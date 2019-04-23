#pragma once

class ParticleS;

class Updater
{
public:
	static void		update(const ParticleS & ps);

	static void		updateParticles(const ParticleS & ps);
	static void		updatePoints(const ParticleS & ps);
	static void		updateWindowTitle(const ParticleS & ps);

};
