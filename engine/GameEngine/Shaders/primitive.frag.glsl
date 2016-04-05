#version 150

in vec4 Color;
in vec4 position;
out vec4 fragmentColor;


void main() {
    
    fragmentColor = Color;
    
    
    vec3 normal = normalize(cross(dFdx(position).xyz,dFdy(position).xyz));
    
    
    vec3 lightDirection = normalize(vec3(0.5,1,1));
    
    float intensity = dot(normal, lightDirection);
    
    //vec3 lightColor = vec3(0.5,0,0);
    
    vec4 baseLight = Color * 0.5;
    
    //fragmentColor = vec4(lightColor * intensity + vec3(0.5,0,0),1);
    fragmentColor = vec4(Color.rgb * intensity,1);
}
//dFdx  give partial deriv of frag nex to it in memory