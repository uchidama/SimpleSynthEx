/*
  ==============================================================================

    SinOscillator.h
    Created: 4 Feb 2021 2:40:29pm
    Author:  masatoshi.uchida

  ==============================================================================
*/

#pragma once

//円周率とsin()関数、midiのあれこれを利用したいので
#include "JuceHeader.h"

class SineOscillator {
public:
	void midiOn(int midiNoteNumber, double hostSampleRate);	//midiOn入力があった時の処理
	void midiOff();			//midiOff入力があった時の処理
	double get();			//現在サンプル時間のSine波を取得
	void phaseIncrement();	//1サンプル時間進める

private:
	bool _midiInput = false;	//現在、OscにMidiOn状態なのかOff状態なのか
	double _n = 0;				//波形生成を開始してからの経過サンプル時間 (周期化するので整数値以外も取りうる)
	double _f = 440;			//周波数
	double _p = 100;			//周期 (サンプル時間)
};
