#include <color_chooser.hpp>

CRGB ColorChooser::colors[USED_COLORS] = {CRGB::Aqua, CRGB::Coral, CRGB::Red, CRGB::Green};

CRGB ColorChooser::getNextColor(CRGB actColor)
{
    // wir durchlaufen alle unsere Farben und gucken, ob
    // die Uebergebene dabei ist
    for (uint8_t i = 0; i < USED_COLORS; i++)
    {
        if (actColor == colors[i])
        {
            // wir haben einen Treffer!!!!
            // sind wir schon am Ende des Arrays?
            if (i < (USED_COLORS - 1))
            {
                // nein - naechste Farbe zurueckgeben
                return colors[i + 1];
            }
            else
            {
                // ja - erste Farbe zurueckgeben
                return colors[0];
            }
        }
    }
    return colors[0];
}

CRGB ColorChooser::getPreviousColor(CRGB actColor)
{
    // wir durchlaufen alle unsere Farben und gucken, ob
    // die Uebergebene dabei ist
    for (uint8_t i = 0; i < USED_COLORS; i++)
    {
        if (actColor == colors[i])
        {
            // wir haben einen Treffer!!!!
            // sind wir am Anfang des Arrays?
            if (i == 0)
            {
                // nein - letzte Farbe zurueckgeben
                return colors[USED_COLORS - 1];
            }
            else
            {
                // nein - vorherige Farbe zurueckgeben
                return colors[i - 1];
            }
        }
    }
    return colors[0];
}
