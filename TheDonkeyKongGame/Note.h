#include <Windows.h>
#include <iostream>
#include "gameConfig.h"
struct Note {
    DWORD frequency;  // Frequency in Hz
    DWORD duration;   // Duration in milliseconds
};

enum class NOTES {
    C3 = 130,  // C3 - 130.81 Hz
    CSharp3 = 139,  // C#3 - 138.59 Hz
    D3 = 146,  // D3 - 146.83 Hz
    DSharp3 = 155,  // D#3 - 155.56 Hz
    E3 = 164,  // E3 - 164.81 Hz
    F3 = 174,  // F3 - 174.61 Hz
    FSharp3 = 185,  // F#3 - 185.00 Hz
    G3 = 196,  // G3 - 196.00 Hz
    GSharp3 = 208,  // G#3 - 207.65 Hz
    A3 = 220,  // A3 - 220.00 Hz
    ASharp3 = 233,  // A#3 - 233.08 Hz
    B3 = 246,  // B3 - 246.94 Hz
    C4 = 261,  // C4 (Middle C) - 261.63 Hz
    CSharp4 = 277,  // C#4 - 277.18 Hz
    D4 = 293,  // D4 - 293.66 Hz
    DSharp4 = 311,  // D#4 - 311.13 Hz
    E4 = 329,  // E4 - 329.63 Hz
    F4 = 349,  // F4 - 349.23 Hz
    FSharp4 = 370,  // F#4 - 369.99 Hz
    G4 = 392,  // G4 - 392.00 Hz
    GSharp4 = 415,  // G#4 - 415.30 Hz
    A4 = 440,  // A4 - 440.00 Hz
    ASharp4 = 466,  // A#4 - 466.16 Hz
    B4 = 493,  // B4 - 493.88 Hz
    C5 = 523,  // C5 - 523.25 Hz
    CSharp5 = 554,  // C#5 - 554.37 Hz
    D5 = 587,  // D5 - 587.33 Hz
    DSharp5 = 622,  // D#5 - 622.25 Hz
    E5 = 659,  // E5 - 659.26 Hz
    F5 = 698,  // F5 - 698.46 Hz
    FSharp5 = 740,  // F#5 - 739.99 Hz
    G5 = 784,  // G5 - 783.99 Hz
    GSharp5 = 830,  // G#5 - 830.61 Hz
    A5 = 880,  // A5 - 880.00 Hz
    ASharp5 = 932,  // A#5 - 932.33 Hz
    B5 = 987,  // B5 - 987.77 Hz
    C6 = 1047,  // C6 - 1046.50 Hz
	BREAK = 0,  // No sound
};

static constexpr int BPM = 150;
static constexpr int BEAT_DURATION_MS = 60000 / BPM;

enum class DURATION_IN_MILLISECONDS {
    QUARTER_NOTE = BEAT_DURATION_MS,      // A quarter note lasts for 1 beat
    HALF_NOTE = BEAT_DURATION_MS * 2,     // A half note lasts for 2 beats
    WHOLE_NOTE = BEAT_DURATION_MS * 4,    // A whole note lasts for 4 beats
    DOTTED_QUARTER_NOTE = BEAT_DURATION_MS * 3 / 2, // A dotted quarter note lasts for 1.5 beats
    EIGHTH_NOTE = BEAT_DURATION_MS / 2,   // An eighth note lasts for half a beat
    DOTTED_EIGHTH_NOTE = BEAT_DURATION_MS / 4 * 3, // A dotted eighth note lasts for 0.75 beats
    SIXTEENTH_NOTE = BEAT_DURATION_MS / 4, // A sixteenth note lasts for a quarter of a beat
    THIRTY_SECOND_NOTE = BEAT_DURATION_MS / 8, // A thirty-second note lasts for an eighth of a beat
    TRIPLETA = BEAT_DURATION_MS / 3,      // A triplet lasts for 1/3 of a beat
    DOTTED_HALF_NOTE = BEAT_DURATION_MS * 3,  // A dotted half note lasts for 3 beats
	
};


Note donkeyStartTheme[] = {
   {  static_cast<DWORD>(NOTES::C3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::DOTTED_QUARTER_NOTE) },
   {  static_cast<DWORD>(NOTES::D3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::DSharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
   {  static_cast<DWORD>(NOTES::C3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
   {  static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::FSharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::FSharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::FSharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::FSharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
   {  static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::WHOLE_NOTE) },

};

Note donkeyHowHighCanYouGet[] = {
   {  static_cast<DWORD>(NOTES::C4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::D4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::F4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
   {  static_cast<DWORD>(NOTES::D4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::C4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::D4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::ASharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::D3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::E3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::F3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::GSharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::A3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::ASharp3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
   {  static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },

};

Note marioTheme[] = {
    // ^E ^E ^E
    { static_cast<DWORD>(NOTES::E4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::E4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
	{ static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::E4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::C4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::E4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::SIXTEENTH_NOTE) },
    { static_cast<DWORD>(NOTES::G4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::HALF_NOTE) },
     { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::HALF_NOTE) },

    { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },

    { static_cast<DWORD>(NOTES::C4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
     { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::E3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },

     { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::A4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::B4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
     { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::ASharp4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::A4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },

    
    { static_cast<DWORD>(NOTES::G3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::E4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::G4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::A4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },

    // ^F ^G ^E ^C ^D B
    { static_cast<DWORD>(NOTES::F4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::G4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::E4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::C4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::D4), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::B3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::QUARTER_NOTE) },
    { static_cast<DWORD>(NOTES::BREAK), static_cast<DWORD>(DURATION_IN_MILLISECONDS::EIGHTH_NOTE) },
    { static_cast<DWORD>(NOTES::C3), static_cast<DWORD>(DURATION_IN_MILLISECONDS::WHOLE_NOTE) },
     

};

void playDonkeyStartTheme() {
    clrsrc();
    gotoxy(gameConfig::GAME_WIDTH / 3, gameConfig::GAME_HEIGHT / 2);
    std::cout << "Playing 'Original Donkey Kong' Theme...\n";
    gotoxy(gameConfig::GAME_WIDTH / 3, gameConfig::GAME_HEIGHT / 2 + 1);
    std::cout << "Press any key to stop\n";
    for (const auto& note : donkeyStartTheme) {
        Beep(note.frequency, note.duration);
        if (_kbhit())
            break;
    }
    gotoxy(0, 0);
}

void playMarioTheme() {
	clrsrc();
    gotoxy(gameConfig::GAME_WIDTH / 3, gameConfig::GAME_HEIGHT / 2);
    std::cout << "Playing Mario Theme...\n";
    gotoxy(gameConfig::GAME_WIDTH / 3, gameConfig::GAME_HEIGHT / 2 + 1);
	std::cout << "Press any key to stop\n";

    for (const auto& note : marioTheme) {
        Beep(note.frequency, note.duration);
		if (_kbhit())
			break;
    }
    gotoxy(0, 0);
}

void playHowHighCanYouGetTheme() {
	for (const auto& note : donkeyHowHighCanYouGet) {
		Beep(note.frequency, note.duration);
		Sleep(1);
	}
}

