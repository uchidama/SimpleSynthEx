/*
  =============================================================================

    SineOscillator.cp
    Created: 4 Feb 2021 2:41:00p
    Author:  masatoshi.uchid

  =============================================================================
*/

#include "SineOscillator.h"

void SineOscillator::midiOn(int midiNoteNumber, double hostSampleRate) {
	//各種パラメータを計算・設定
	_midiInput = true;
	_n = 0;    	_f =juce:: MidiMessage::getMidiNoteInHertz(midiNoteNumber);	//midiNote番号はただの整数値なので周波数Hzに変換
	_p = hostSampleRate / _f;
}

void SineOscillator::midiOff() {
	_midiInput = false;
	//midiがoffになったら波形生成をやめるので、Sine波の計算に必要な他パラメータは計算・設定する必要無し
}

double SineOscillator::get() {
	if (!_midiInput) { return 0.0; }

	//sin(w * t) = sin(2 * pi * f * n / fs)
	return sin(2.0 *juce:: double_Pi * _n / _p);
}

void SineOscillator::phaseIncrement() {
	//1サンプル時間進めて、必要に応じて周期化
	if (++_n >= _p) { _n = _n - int(_n / _p) * _p; }
}



