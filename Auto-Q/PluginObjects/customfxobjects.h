#pragma once
#include "fxobjects.h"

/**
\struct AutoQEnvelopeFollowerParameters
\ingroup FX-Objects
\brief
Custom parameter structure for the AutoQEnvelopeFollower object.

\author Steve Dwyer - Adapted from Will Pirkle http://www.willpirkle.com
\remark This object is based on the EnvelopeFollowerParameters class included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
struct AutoQEnvelopeFollowerParameters
{
	AutoQEnvelopeFollowerParameters()
	{
	}

	/** all FXObjects parameter objects require overloaded= operator so remember to add new entries if you add new variables. */
	AutoQEnvelopeFollowerParameters& operator=(const AutoQEnvelopeFollowerParameters& params)
	// need this override for collections to work
	{
		if (this == &params)
			return *this;

		// Filter parameters
		filterAlgorithm = params.filterAlgorithm;
		fc = params.fc;
		Q = params.Q;
		filterOutputGain_dB = params.filterOutputGain_dB;
		enableGainComp = params.enableGainComp;
		matchAnalogNyquistLPF = params.matchAnalogNyquistLPF;
		selfOscillate = params.selfOscillate;
		enableNLP = params.enableNLP;

		// Detector parameters
		attackTime_mSec = params.attackTime_mSec;
		releaseTime_mSec = params.releaseTime_mSec;
		threshold_dB = params.threshold_dB;
		sensitivity = params.sensitivity;

		return *this;
	}

	// Filter parameters
	vaFilterAlgorithm filterAlgorithm = vaFilterAlgorithm::kSVF_LP; ///< va filter algorithm
	double fc = 1000.0; ///< va filter fc
	double Q = 0.707; ///< va filter Q
	double filterOutputGain_dB = 0.0; ///< va filter gain (normally unused)
	bool enableGainComp = false; ///< enable gain compensation (see book)
	bool matchAnalogNyquistLPF = true; ///< match analog gain at Nyquist
	bool selfOscillate = false; ///< enable selfOscillation
	bool enableNLP = true; ///< enable non linear processing (use oversampling for best results)

	// Detector parameters
	double attackTime_mSec = 20.0; ///< detector attack time
	double releaseTime_mSec = 500.0; ///< detector release time
	double threshold_dB = -6.0; ///< detector threshold in dB
	double sensitivity = 1.0; ///< detector sensitivity
};

/**
\class EnvelopeFollower
\ingroup FX-Objects
\brief
The EnvelopeFollower object implements a traditional envelope follower effect modulating a LPR fc value
using the strength of the detected input.

Audio I/O:
- Processes mono input to mono output.

Control I/F:
- Use EnvelopeFollowerParameters structure to get/set object params.

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class AutoQEnvelopeFollower : public IAudioSignalProcessor
{
public:
	AutoQEnvelopeFollower()
	{
		// --- setup the filter
		ZVAFilterParameters filterParams;
		filterParams.filterAlgorithm = vaFilterAlgorithm::kSVF_LP;
		filterParams.fc = 1000.0;
		filterParams.enableGainComp = false;
		filterParams.matchAnalogNyquistLPF = true;
		filterParams.selfOscillate = false;
		filterParams.enableNLP = true;
		filter.setParameters(filterParams);

		// --- setup the detector
		AudioDetectorParameters adParams;
		adParams.attackTime_mSec = 20.0;
		adParams.releaseTime_mSec = 500.0;
		adParams.detectMode = TLD_AUDIO_DETECT_MODE_RMS;
		adParams.detect_dB = true;
		adParams.clampToUnityMax = false;
		detector.setParameters(adParams);
	} /* C-TOR */
	~AutoQEnvelopeFollower()
	{
	} /* D-TOR */

	/** reset members to initialized state */
	virtual bool reset(double _sampleRate)
	{
		filter.reset(_sampleRate);
		detector.reset(_sampleRate);
		return true;
	}

	/** get parameters: note use of custom structure for passing param data */
	/**
	\return EnvelopeFollowerParameters custom data structure
	*/
	AutoQEnvelopeFollowerParameters getParameters() { return parameters; }

	static bool isFloatEqual(const double a, const double b)
	{
		return fabs(a - b) < FLT_EPSILON;
	}

	static bool filterParametersUpdated(const ZVAFilterParameters filterParams, const AutoQEnvelopeFollowerParameters& params)
	{
		return filterParams.filterAlgorithm != params.filterAlgorithm ||
			!isFloatEqual(filterParams.fc, params.fc) ||
			!isFloatEqual(filterParams.Q, params.Q) ||
			!isFloatEqual(filterParams.enableGainComp, params.enableGainComp) ||
			!isFloatEqual(filterParams.filterOutputGain_dB, params.filterOutputGain_dB) ||
			filterParams.matchAnalogNyquistLPF != params.matchAnalogNyquistLPF ||
			filterParams.enableNLP != params.enableNLP ||
			filterParams.selfOscillate != params.selfOscillate;
	}


	void updateFilterParameters(const AutoQEnvelopeFollowerParameters& params)
	{
		ZVAFilterParameters filterParams = filter.getParameters();
		if (filterParametersUpdated(filterParams, params))
		{
			filterParams.filterAlgorithm = params.filterAlgorithm;
			filterParams.fc = params.fc;
			filterParams.Q = params.Q;
			filterParams.enableGainComp = params.enableGainComp;
			filterParams.filterOutputGain_dB = params.filterOutputGain_dB;
			filterParams.matchAnalogNyquistLPF = params.matchAnalogNyquistLPF;
			filterParams.enableNLP = params.enableNLP;
			filterParams.selfOscillate = params.selfOscillate;
			filter.setParameters(filterParams);
		}
	}
	static bool detectorParametersUpdated(const AudioDetectorParameters adParams, const AutoQEnvelopeFollowerParameters& params)
	{
		return !isFloatEqual(adParams.attackTime_mSec, params.attackTime_mSec) ||
			!isFloatEqual(adParams.releaseTime_mSec, params.releaseTime_mSec);
	}

	void updateDetectorParameters(const AutoQEnvelopeFollowerParameters& params)
	{
		AudioDetectorParameters adParams = detector.getParameters();

		if (detectorParametersUpdated(adParams, params))
		{
			adParams.attackTime_mSec = params.attackTime_mSec;
			adParams.releaseTime_mSec = params.releaseTime_mSec;
			detector.setParameters(adParams);
		}
	}

	/** set parameters: note use of custom structure for passing param data */
	/**
	\param params custom data structure
	*/
	void setParameters(const AutoQEnvelopeFollowerParameters& params)
	{
		updateFilterParameters(params);
		updateDetectorParameters(params);

		// --- save
		parameters = params;
	}

	/** return false: this object only processes samples */
	virtual bool canProcessAudioFrame() { return false; }

	/** process input x(n) through the envelope follower to produce return value y(n) */
	/**
	\param xn input
	\return the processed sample
	*/
	virtual double processAudioSample(double xn)
	{
		// --- calc threshold
		double threshValue = pow(10.0, parameters.threshold_dB / 20.0);

		// --- detect the signal
		double detect_dB = detector.processAudioSample(xn);
		double detectValue = pow(10.0, detect_dB / 20.0);
		double deltaValue = detectValue - threshValue;

		ZVAFilterParameters filterParams = filter.getParameters();
		filterParams.fc = parameters.fc;
		filterParams.Q = parameters.Q;

		// --- if above the threshold, modulate the filter fc
		if (deltaValue > 0.0) // || delta_dB > 0.0)
		{
			// --- fc Computer
			double modulatorValue = 0.0;

			// --- best results are with linear values when detector is in dB mode
			modulatorValue = (deltaValue * parameters.sensitivity);

			// --- calculate modulated frequency
			filterParams.fc = doUnipolarModulationFromMin(modulatorValue, parameters.fc, kMaxFilterFrequency);
		}

		// --- update with new modulated frequency
		filter.setParameters(filterParams);

		// --- perform the filtering operation
		return filter.processAudioSample(xn);
	}

protected:
	AutoQEnvelopeFollowerParameters parameters; ///< object parameters

	// --- 1 filter and 1 detector
	ZVAFilter filter; ///< filter to modulate
	AudioDetector detector; ///< detector to track input signal
};
