float calcAvg(float *values, long currentNumValidValues)
{
    float sum = 0;
    for (long i = 0; i < currentNumValidValues; i++)
    { // Corrected loop initialization
        sum += values[i];
    }
    if (currentNumValidValues > 0)
    {
        return sum / currentNumValidValues;
    }
    else
    {
        return 0.0; // Avoid division by zero
    }
}

float calcMax(float *values, long currentNumValidValues)
{
    if (currentNumValidValues == 0)
    {
        return 0.0; // Or -FLT_MAX, depending on desired behavior for empty buffer
    }

    float val = values[0]; // Initialize with the first valid element
    for (long i = 1; i < currentNumValidValues; i++)
    { // Corrected loop initialization
        if (values[i] > val)
        { // Corrected logic: find greater value
            val = values[i];
        }
    }
    return val;
}

float calcMin(float *values, long currentNumValidValues)
{
    if (currentNumValidValues == 0)
    {
        return 0.0; // Or -FLT_MAX, depending on desired behavior for empty buffer
    }

    float val = values[0]; // Initialize with the first valid element
    for (long i = 1; i < currentNumValidValues; i++)
    { // Corrected loop initialization
        if (values[i] < val)
        { // Corrected logic: find greater value
            val = values[i];
        }
    }
    return val;
}