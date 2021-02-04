/*
  =============================================================================
    Synth.c
    Created: 4 Feb 2021 2:42:54
    Author:  masatoshi.uchid
  ============================================================================
*/
#include "Synth.h"

using namespace syn;

void Synth::midiProcessing(juce::MidiMessage& m, double hostSampleRate) {
	//受けとったMidiがOn信号だった場合
	//midi信号からノート番号を取り出し、Oscを走らせる
	if (m.isNoteOn()) { oscillator.midiOn(m.getNoteNumber(), hostSampleRate); }
	else { oscillator.midiOff(); }
}

void Synth::renderWaveData(float* hostAudioBuffer, int bufferSize) {
	//bufferSizeサンプル時間分Sine波を生成
	//1サンプル時間レンダリングするたびに、Oscの経過サンプル時間を進める
	for (int n = 0; n < bufferSize; n++) {
		hostAudioBuffer[n] = oscillator.get();
		oscillator.phaseIncrement();
	}
}

void syn::doProcessing(Synth& sy,juce::AudioSampleBuffer& audioBuff,juce::MidiBuffer& midiBuff, double hostSampleRate) {

    //midiの処理
	juce::MidiBuffer::Iterator itr(midiBuff);
	juce::MidiMessage message(0);		//デフォルトでNoteOff
	int midiPosition;			//この変数の値は実際には使用しない
    
	//受け取ったmidiBufferを走査し、midi入力が存在するかを探索
	//midi入力があれば、getNextEventの第一引数にmidiデータ、第二引数にmidiデータの位置が書き込まれ、trueを返す
	//今回、第二引数の情報は使用しない
	while (itr.getNextEvent(message, midiPosition)) {
		sy.midiProcessing(message, hostSampleRate);
	}

	//audioの処理
	//この辺の宣言については、"JUCE JAPAN"参照
	float* leftChannelAudio = audioBuff.getWritePointer(0);
	float* rigthChannelAudio = audioBuff.getWritePointer(1);
	int buffSize = audioBuff.getNumSamples();

	//hostAudioBufferにSine波をレンダリング
	sy.renderWaveData(leftChannelAudio, buffSize);

	//とりあえず、モノラル処理で
	for (int n = 0; n < buffSize; n++) { rigthChannelAudio[n] = leftChannelAudio[n]; }


}