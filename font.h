#pragma once

#ifndef FONTS_H
#define FONTS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class FontManager {
public:
    static Font defaultFont;
    static bool initialized;

    static bool initialize() {
        if (initialized) return true;

        // Create a default font programmatically
        const unsigned char fontData[] = {
            // Basic data structure for a minimal font
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, /* Basic font data structure */
            // More data here...
        };

        // Try to load from memory
        if (!defaultFont.loadFromMemory(fontData, sizeof(fontData))) {
            cout << "Failed to load built-in font!" << endl;
            return false;
        }

        initialized = true;
        return true;
    }

    // Draw simple text (even without a font)
    static void drawText(RenderWindow& window, const string& text,
        float x, float y, int size, Color color) {
        if (initialized) {
            Text sfText(text, defaultFont, size);
            sfText.setPosition(x, y);
            sfText.setFillColor(color);
            window.draw(sfText);
        }
        else {
            // Fallback to drawing simple rectangles for text
            for (size_t i = 0; i < text.length(); i++) {
                RectangleShape rect;
                rect.setSize(Vector2f(size / 2.0f, size));
                rect.setFillColor(color);
                rect.setPosition(x + i * (size / 1.5f), y);
                window.draw(rect);
            }
        }
    }
};

// Static variable initialization
Font FontManager::defaultFont;
bool FontManager::initialized = false;

#endif // FONTS_H