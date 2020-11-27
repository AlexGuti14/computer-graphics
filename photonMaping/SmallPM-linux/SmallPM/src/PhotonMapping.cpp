/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 

This software is provided as is, and any express or implied warranties are disclaimed.
In no event shall copyright holders be liable for any damage.
**********************************************************************************/
#include "PhotonMapping.h"
#include "World.h"
#include "Intersection.h"
#include "Ray.h"
#include "BSDF.h"
#include <math.h>
#include <random>

//*********************************************************************
// Compute the photons by tracing the Ray 'r' from the light source
// through the scene, and by storing the intersections with matter
// in the lists 'xx_photons', storing the diffuse (global) and caustic
// photons respectively. For efficiency, both are computed at the same
// time, since computing them separately would result into a lost of
// several samples marked as caustic or diffuse.
// Same goes with the boolean 'direct', that specifies if direct 
// photons (from light to surface) are being stored or not. 
// The initial traced photon has energy defined by the tristimulus
// 'p', that accounts for the emitted power of the light source.
// The function will return true when there are more photons (caustic
// or diffuse) to be shot, and false otherwise.
//---------------------------------------------------------------------
bool PhotonMapping::trace_ray(const Ray& r, const Vector3 &p, 
			   std::list<Photon> &global_photons, std::list<Photon> &caustic_photons, bool direct, bool direct_only)
{
#ifndef MAX_PHOTON_ITERATIONS
#define MAX_PHOTON_ITERATIONS 20
#endif



	//Check if max number of shots done...
	if( ++m_nb_current_shots > m_max_nb_shots )
	{
		return false;
	}
	
	// Compute irradiance photon's energy
	Vector3 energy(p);
	
	Ray photon_ray(r);
	photon_ray.shift();

	bool is_caustic_particle = false;
	//Iterate the path
	while(1)
	{
		// Throw ray and update current_it
		Intersection it;
		// Return the object that first intersects
		world->first_intersection(photon_ray, it);


		if( !it.did_hit() )
			break;

		//Check if has hit a delta material...
		if( it.intersected()->material()->is_delta() )
		{
			// If delta material, then is caustic...
			// Don't store the photon!
			is_caustic_particle = true;
		}
		else if (photon_ray.get_level() > 0 || direct || direct_only )
		{
			//If non-delta material, store the photon!
			if( is_caustic_particle )	
			{				
				//If caustic particle, store in caustics
				if( caustic_photons.size() < m_nb_caustic_photons )
					caustic_photons.push_back( Photon(it.get_position(), photon_ray.get_direction(), energy ));
			}
			else						
			{
				//If non-caustic particle, store in global
				if( global_photons.size() < m_nb_global_photons )
					global_photons.push_back( Photon(it.get_position(), photon_ray.get_direction(), energy ));
			}
			is_caustic_particle = false;
		}	
		
		Real pdf;

		Vector3 surf_albedo = it.intersected()->material()->get_albedo(it);
		Real avg_surf_albedo = surf_albedo.avg();

		Real epsilon2 = static_cast<Real>(rand())/static_cast<Real>(RAND_MAX);
		while (epsilon2 < 0.)
			epsilon2 = static_cast<Real>(rand())/static_cast<Real>(RAND_MAX);
		
		if (epsilon2 > avg_surf_albedo || photon_ray.get_level() > MAX_PHOTON_ITERATIONS ) 
			break;
		
		if (direct_only && !is_caustic_particle && photon_ray.get_level() > 1)
			break;

		// Random walk's next step
		// Get sampled direction plus pdf, and update attenuation
		it.intersected()->material()->get_outgoing_sample_ray(it, photon_ray, pdf);

		// Shade...
		energy = energy*surf_albedo;
		if( !it.intersected()->material()->is_delta() )
			energy *= dot_abs(it.get_normal(), photon_ray.get_direction())/3.14159;		

		energy = energy /(pdf*avg_surf_albedo);
	}
	
	if( caustic_photons.size() == m_nb_caustic_photons && 
		global_photons.size() == m_nb_global_photons )
	{
		m_max_nb_shots = m_nb_current_shots-1;
		return false;
	}

	return true;
}

//*********************************************************************
// TODO: Implement the preprocess step of photon mapping,
// where the photons are traced through the scene. To do it,
// you need to follow these steps for each shoot:
//  1 - Sample a world's light source in the scene to create
//		the initial direct photon from the light source.
//	2 - Trace the photon through the scene storing the inter-
//		sections between the photons and matter. You can use
//		the function 'trace_ray' for this purpose.
//	3 - Finally, once all the photons have been shot, you'll
//		need to build the photon maps, that will be used later
//		for rendering. 
//		NOTE: Careful with function
//---------------------------------------------------------------------
void PhotonMapping::preprocess()
{
	//Lista de fotones
	list<Photon> global_photons, caustics_photons;
    //Direccion del rayo
	Vector3 dir;
	//Coordenadas aleatorias de la direccion del rayo
	Real x, y, z;
	default_random_engine generator;
    uniform_real_distribution<Real> distr = uniform_real_distribution<Real>(-1.0, 1.0);
	//Numero de fotones por fuente de luz
	int num_p = m_max_nb_shots / world->nb_lights();

	bool direct = false;
	bool direct_only = false;

	// Se recorren las diferentes luces
	for (LightSource* l : world->light_source_list) {		
		do {
			// 1 - Sample a world's light source in the scene to create the initial direct photon from the light source
			do {
				// Se calcula dirección aleatoria.
				x = distr(generator);
				y = distr(generator);
				z = distr(generator);
			} while (pow(x,2) + pow(y,2) + pow(z,2) > 1);
			// Se crea el vector con la dirección
			dir = Vector3(x, y, z);
		// 2 - Trace the photon through the scene storing the intersections between the photons and matter.
		// Se ejecuta la funcion 'trace_ray' para trazar el fotón a través de la escena 
		// almacenando las intersecciones con la materia en las listas
		//Escena es de -1,1, hacer en rango de la esfera, volumen de la esfera 1/4pi^2
		} while (trace_ray(Ray(l->get_position(), dir), Vector3(4 * M_PI * l->get_intensities() / num_p), global_photons, caustics_photons, direct, direct_only));
	}


	// 3 - Se construyen los 2 mapas de fotones globales y causticas recorriendo las listas
	for (Photon p : global_photons) {m_global_map.store({p.position[0], p.position[1], p.position[2]}, p);}
	for (Photon p : caustics_photons) {m_caustics_map.store({p.position[0], p.position[1], p.position[2]}, p);}
	
	// Balanceo de mapas
	if (!global_photons.empty()) {
		m_global_map.balance();
	}
	if (!caustics_photons.empty()) {
		m_caustics_map.balance();
	}
}


//*********************************************************************
// Devuelve la BRDF en función de si el material es Lambertiano o de Phong 
//---------------------------------------------------------------------
Vector3 getBRDF(Intersection it, Vector3 wi){
	Vector3 brdf;
	Real alpha = it.intersected()->material()->get_specular(it);
	Vector3 albedo = it.intersected()->material()->get_albedo(it);

	if (alpha == 0. || alpha == INFINITY){
		//Lambertiano
		brdf = albedo / M_PI;
	}
	else
	{
		//Phong
		Vector3 wo = it.get_ray().get_direction();
		Vector3 wr = wi.reflect(it.get_normal());
		brdf = albedo * (alpha + 2) * powf(wo.dot_abs(wr), alpha) / (2 * M_PI);
	}

	return brdf;
}

//*********************************************************************
// TODO: Implement the function that computes the rendering equation 
// using radiance estimation with photon mapping, using the photon
// maps computed as a preprocess. Note that you will need to handle
// both direct and global illumination, together with recursive the 
// recursive evaluation of delta materials. For an optimal implemen-
// tation you should be able to do it iteratively.
// In principle, the class is prepared to perform radiance estimation
// using k-nearest neighbors ('m_nb_photons') to define the bandwidth
// of the kernel.
//---------------------------------------------------------------------
Vector3 PhotonMapping::shade(Intersection &it0)const
{
	Vector3 L(0);
	Vector3 W(1);
	
	Intersection it(it0);

	//**********************************************************************
	// The following piece of code is included here for two reasons: first
	// it works as a 'hello world' code to check that everthing compiles 
	// just fine, and second, to illustrate some of the functions that you 
	// will need when doing the work. Goes without saying: remove the 
	// pieces of code that you won't be using.
	//
	unsigned int debug_mode = 7;

	switch (debug_mode)
	{
	case 1:
		// ----------------------------------------------------------------
		// Display Albedo Only
		L = it.intersected()->material()->get_albedo(it);
		break;
	case 2:
		// ----------------------------------------------------------------
		// Display Normal Buffer
		L = it.get_normal();
		break;
	case 3:
		// ----------------------------------------------------------------
		// Display whether the material is specular (or refractive) 
		L = Vector3(it.intersected()->material()->is_delta());
		break;

	case 4:
		// ----------------------------------------------------------------
		// Display incoming illumination from light(0)
		L = world->light(0).get_incoming_light(it.get_position());
		break;

	case 5:
		// ----------------------------------------------------------------
		// Display incoming direction from light(0)
		L = world->light(0).get_incoming_direction(it.get_position());
		break;

	case 6:
		// ----------------------------------------------------------------
		// Check Visibility from light(0)
		if (world->light(0).is_visible(it.get_position()))
			L = Vector3(1.);
		break;
	case 7:
		// ----------------------------------------------------------------

		// Numero de rebotes
		int nb_bounces = 0;
		// MAX_NB_BOUNCES defined in ./SmallRT/include/globals.h

		// Reflect and refract until a diffuse surface is found
		// Trazado de rayos desde la camara
		while (it.intersected()->material()->is_delta() && ++nb_bounces < MAX_NB_BOUNCES) {
			Ray r; float pdf;
			it.intersected()->material()->get_outgoing_sample_ray(it, r, pdf );		
			W = W * it.intersected()->material()->get_albedo(it)/pdf;
			r.shift();
			world->first_intersection(r, it);
		}

		if (!it.intersected()->material()->is_delta()) {

			//////////////		Direct light		//////////////
			Vector3 Ld(0,0,0);

			// Intensidad luz -> get_incoming_light   Li(x,wi)
			// Dir del rayo desde la luz al punto -> get_incoming_direction (dirección de sombra)
			
			// Se recorren todas las fuentes de luz
			for (LightSource* l : world->light_source_list) {
				if (l->is_visible(it.get_position())) {
					Vector3 wi = l->get_incoming_direction(it.get_position()).normalize() * -1;
					Ld += l->get_incoming_light(it.get_position()) * getBRDF(it,wi) 
					* dot_abs(l->get_incoming_direction(it.get_position()),it.get_normal());
				}
			}


			// Estimacion de radiancia
			//////////////		Indirect light		//////////////
			Vector3 Li(0,0,0);

			// Vector para los fotones más cercanos
			vector<const KDTree<Photon, 3>::Node*> global_photons;
			Real max_distanceG = 0;
			//Punto de referencia
			vector<Real> point = {it.get_position().getComponent(0), it.get_position().getComponent(1), it.get_position().getComponent(2)};

			// Busqueda de los fotones más cercanos y la maxima distancia
			m_global_map.find(point, m_nb_photons, global_photons, max_distanceG);

			//Filtro de cono
			Real k = 1.5;		// Parámetro del filtro de cono
			for (const KDTree<Photon, 3>::Node* g : global_photons) {
				// ECUACION DE RENDER (sumatorio de flujos de fotones * BRDF * wp)				
				Real distancia = (g->data().position - it.get_position()).length();
				Real wp = 1 - (distancia / k * max_distanceG);
				Vector3 wi = g->data().direction * -1;
				Li += g->data().flux * getBRDF(it,wi) * wp;
				
			}
			Li = Li / ((1 - (2.0 / (3.0*k))) * M_PI * pow(max_distanceG, 2));



			//////////////		CAUSTICS	//////////////
			Vector3 Lc(0,0,0);

			// Vector para los fotones más cercanos
			vector<const KDTree<Photon, 3>::Node*> caustics_photons;
			Real max_distanceC = 0;
			
			// Busqueda de los fotones más cercanos y la maxima distancia
			m_caustics_map.find(point, m_nb_photons, caustics_photons, max_distanceC);

			//Filtro de cono
			for (const KDTree<Photon, 3>::Node* c : caustics_photons) {
				// ECUACION DE RENDER (sumatorio de flujos de fotones * BRDF * wp)
				Real distancia = (c->data().position - it.get_position()).length();
				Real wp = 1 - (distancia / k * max_distanceC);
				Vector3 wi = c->data().direction * -1;
				Lc += c->data().flux * getBRDF(it,wi) * wp;
			}
			Lc = Lc / ((1 - (2.0 / (3.0*k))) * M_PI * pow(max_distanceC, 2));


			L = Ld + Li + Lc;
		}
	}

	return L*W;
}