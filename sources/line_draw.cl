// simple kernel that copy in into out

static float luminosity(float4 col) {
    return 0.21f * col.x + 0.72f * col.y + 0.07f * col.z;
}

static float4 pattern(int2 loc) {
//    const int depth = (loc.x + loc.y) % 32;
    const int depth = 16;
    float a = ((float)((loc.x * 2 + loc.y) % depth) / (float)depth);
    float b = ((float)((loc.y * 2 + loc.x) % depth) / (float)depth);
    float c = ((float)((loc.x + loc.y) % depth) / (float)depth);
    return (float4)(a, b, c, 1.0f);
}

static float4 RGB2CMY(float4 rgb) {
    return (float4)(1.0f - rgb.x, 1.0f - rgb.y, 1.0f -rgb.z, 1.0f);
}

__kernel void video_image(
    __read_only image2d_t in,
    __write_only image2d_t out)
{
    const sampler_t format =
        CLK_NORMALIZED_COORDS_FALSE |
        CLK_FILTER_NEAREST |
        CLK_ADDRESS_CLAMP;
    const int2 d = (int2)(get_global_id(0), get_global_id(1));
    float4 col = read_imagef(in, format, d);
    // init output image
    float4 pat = pattern(d);
    float4 res = RGB2CMY(col) * pat;
    float4 oc = (float4)(
        (res.x > 0.5f) ? 1.0f : 0.0f,
        (res.y > 0.5f) ? 1.0f : 0.0f,
        (res.z > 0.5f) ? 1.0f : 0.0f,
        1.0f
        );
    write_imagef(out, d, RGB2CMY(oc));
}
