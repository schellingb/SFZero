#ifndef SFZRegion_h
#define SFZRegion_h

#include <math.h>

namespace SFZero {

class SFZSample;


// SFZRegion is designed to be able to be bitwise-copied.

struct SFZEGParameters {
	float	delay, start, attack, hold, decay, sustain, release;
	float	keynumToHold, keynumToDecay;

	void	clear();
	void	clearMod();
	void	sf2ToSFZ(bool sustainIsGain);
	};

class SFZRegion {
	public:
		enum Trigger {
			attack, release, first, legato
			};
		enum LoopMode {
			sample_loop, no_loop, one_shot, loop_continuous, loop_sustain
			};
		enum OffMode {
			fast, normal
			};


		SFZRegion();
		void	clear();
		void	clearForSF2();
		void	clearForRelativeSF2();
		void	addForSF2(SFZRegion* other);
		void	sf2ToSFZ();
		void	dump();

		bool	matches(unsigned char note, unsigned char velocity, Trigger _trigger) {
			return
				note >= lokey && note <= hikey &&
				velocity >= lovel && velocity <= hivel &&
				(_trigger == trigger ||
				 (trigger == attack && (_trigger == first || _trigger == legato)));
			}

		SFZSample* sample;
		unsigned char lokey, hikey;
		unsigned char lovel, hivel;
		Trigger trigger;
		unsigned long group, off_by;
		OffMode off_mode;

		unsigned long offset;
		unsigned long end;
		bool negative_end;
		LoopMode loop_mode;
		unsigned long loop_start, loop_end;
		int transpose;
		int tune;
		int pitch_keycenter, pitch_keytrack;
		int bend_up, bend_down;

		float volume, pan;
		float amp_veltrack;

		SFZEGParameters	ampeg, modeg, ampeg_veltrack;
		int initialFilterQ, initialFilterFc;
		int modEnvToPitch, modEnvToFilterFc;
		float delayModLFO;
		int freqModLFO, modLfoToPitch, modLfoToFilterFc, modLfoToVolume;
		float delayVibLFO;
		int freqVibLFO, vibLfoToPitch;

		static inline double timecents2Secs(double timecents) { return pow(2.0, timecents / 1200.0); }
		static inline float timecents2Secs(float timecents) { return powf(2.0f, timecents / 1200.0f); }
		static inline float cents2Hertz(float cents) { return 8.176f * powf(2.0f, cents / 1200.0f); }
	};

}

#endif 	// !SFZRegion_h

