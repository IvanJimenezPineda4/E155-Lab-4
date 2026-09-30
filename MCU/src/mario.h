// Ivan Jimenez Pineda
// ijimenezpineda@g.hmc.edu
// September 29, 2025
// mario.h contains code to play the Super Mario Bros. Theme!

#ifndef mario_theme
#define mario_theme

// Pitch in Hz, duration in ms
const int mario_notes[][2] = {
    {659,   125}, // E5
    {  0,   125}, // Rest
    {659,   125}, // E5
    {  0,   250}, // Rest
    {659,   125}, // E5
    {  0,   125}, // Rest
    {523,   125}, // C5
    {659,   250}, // E5
    {784,   250}, // G5
    {  0,   250}, // Rest
    {392,   250}, // G4
    {  0,   250}, // Rest
    {523,   250}, // C5
    {  0,   125}, // Rest
    {392,   250}, // G4
    {  0,   125}, // Rest
    {330,   250}, // E4
    {  0,   125}, // Rest
    {440,   250}, // A4
    {494,   250}, // B4
    {466,   125}, // Bb4
    {440,   250}, // A4
    {392,   125}, // G4
    {659,   125}, // E5
    {784,   125}, // G5
    {880,   250}, // A5
    {698,   125}, // F5
    {784,   125}, // G5
    {659,   250}, // E5
    {523,   125}, // C5
    {587,   125}, // D5
    {494,   375}, // B4
    {  0,   250}, // Rest
    {  0,     0}
};

#endif