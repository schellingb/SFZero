#ifndef SFZSample_h
#define SFZSample_h

#include "../JuceLibraryCode/JuceHeader.h"


class SFZSample {
	public:
		SFZSample(const File& fileIn)
			: file(fileIn) {}

		File	getFile() { return file; }
		String	getShortName();
		void	dump();

	protected:
		File	file;
	};


#endif 	// !SFZSample_h
