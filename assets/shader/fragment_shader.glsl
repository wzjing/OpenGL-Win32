#version 330

precision highp float;

out vec4 fragmentColor;

uniform vec2 iResolution;

vec3 getRGB(vec2 uv) {
    vec3 rgb = vec3(sin(uv.x), sin(uv.y), sin(uv.x*uv.y));
    return rgb;
}

void main() {

    vec2 uv = (gl_FragCoord.xy + 0.5)/iResolution.xy;

    fragmentColor = vec4(getRGB(uv), 1.0);

}
