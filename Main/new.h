void porcentaje(float percentage, int color)
{
    int len = matrix[strip];
    center = center % len;
    for (int j = 0; j < len; j++)
    {
        float distance;

        FastLED.clear();
        for (int i = 0; i < NUM_STRIPS; i++)
            if ((center - j) > len * 0.5)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (j < percentage * 10)
                    {
                        leds[i][j] = CHSV(color, 255, 255);
                    }
                }
            }
        FastLED.show();
        distance = abs(center - (j + len));
    }

    void porcentaje(float percentage, int strip, int color)
    {
        FastLED.clear();
        for (int i = 0; i < NUM_STRIPS; i++)
        {
            for (int j = 0; j < NUM_PER_STRIP[i]; j++)
            {
                if (j < percentage * NUM_PER_STRIP[i])
                {
                    leds[i][j] = CHSV(color, 255, 255);
                }
            }
        }
        FastLED.show();
    }

