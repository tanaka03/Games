xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 34;
 0.46727;1.05118;-1.82588;,
 1.41905;0.69127;-0.66339;,
 2.58670;-1.53503;-2.19052;,
 1.52538;-1.13371;-3.48678;,
 1.30925;-0.17763;0.60931;,
 2.46426;-2.50393;-0.77136;,
 0.20219;-1.04654;1.24669;,
 1.22981;-3.47283;-0.06063;,
 -1.25362;-1.40645;0.87538;,
 -0.39354;-3.87416;-0.47468;,
 -2.20540;-1.04654;-0.28712;,
 -1.45486;-3.47283;-1.77095;,
 -2.09560;-0.17763;-1.55982;,
 -1.33242;-2.50393;-3.19012;,
 -0.98855;0.69127;-2.19719;,
 -0.09797;-1.53503;-3.90084;,
 3.33724;-3.96134;-3.67435;,
 2.38546;-3.60143;-4.83684;,
 3.22745;-4.83024;-2.40166;,
 2.12039;-5.69915;-1.76427;,
 0.66458;-6.05905;-2.13559;,
 -0.28720;-5.69915;-3.29808;,
 -0.17740;-4.83024;-4.57079;,
 0.92965;-3.96134;-5.20815;,
 3.27341;-6.03155;-4.69692;,
 2.72390;-5.82375;-5.36808;,
 3.21003;-6.53320;-3.96213;,
 2.57087;-7.03486;-3.59414;,
 1.73035;-7.24266;-3.80852;,
 1.18084;-7.03486;-4.47968;,
 1.24423;-6.53320;-5.21448;,
 1.88339;-6.03155;-5.58246;,
 2.48412;-7.15654;-4.99170;,
 -0.49964;0.08061;-0.30813;;
 
 40;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,17,25,31;,
 3;25,24,32;,
 3;24,26,32;,
 3;26,27,32;,
 3;27,28,32;,
 3;28,29,32;,
 3;29,30,32;,
 3;30,31,32;,
 3;31,25,32;,
 3;33,12,10;,
 3;33,14,12;,
 3;33,0,14;,
 3;33,1,0;,
 3;33,4,1;,
 3;33,6,4;,
 3;33,8,6;,
 3;33,10,8;;
 
 MeshMaterialList {
  4;
  40;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.558431;0.429804;0.649412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.033647;0.033647;0.033647;1.000000;;
   14.000000;
   0.280000;0.280000;0.280000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.557333;0.176000;0.208000;1.000000;;
   18.000000;
   0.700000;0.700000;0.700000;;
   0.131137;0.041412;0.048941;;
  }
  Material {
   0.269804;0.266667;0.489412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  42;
  -0.327087;0.793353;0.513424;,
  0.399106;0.669514;-0.626470;,
  0.869149;0.491771;-0.052365;,
  0.814925;0.062656;0.576169;,
  0.268198;-0.366459;0.890942;,
  -0.450768;-0.544206;0.707565;,
  -0.920813;-0.366460;0.133458;,
  -0.866588;0.062656;-0.495075;,
  -0.319858;0.491771;-0.809847;,
  0.426269;0.608761;-0.669107;,
  0.897785;0.430460;-0.093204;,
  0.843392;0.000001;0.537299;,
  0.294951;-0.430459;0.853059;,
  -0.426268;-0.608761;0.669108;,
  -0.897785;-0.430459;0.093202;,
  -0.843391;0.000001;-0.537301;,
  -0.294948;0.430460;-0.853059;,
  0.489481;0.412403;-0.768331;,
  0.948643;0.238774;-0.207516;,
  0.895677;-0.180407;0.406469;,
  0.361603;-0.599591;0.713957;,
  -0.340721;-0.773221;0.534825;,
  -0.799884;-0.599591;-0.025992;,
  -0.746915;-0.180407;-0.639978;,
  -0.212840;0.238774;-0.947463;,
  0.537056;-0.030088;-0.843010;,
  0.902327;-0.168214;-0.396874;,
  0.860193;-0.501681;0.091563;,
  0.435328;-0.835150;0.336176;,
  -0.123384;-0.973276;0.193673;,
  -0.488656;-0.835150;-0.252466;,
  -0.446518;-0.501682;-0.740903;,
  -0.021650;-0.168214;-0.985513;,
  0.327088;-0.793351;-0.513427;,
  -0.457182;0.783235;0.421339;,
  -0.465843;0.714705;0.521715;,
  -0.369871;0.851765;0.371068;,
  -0.255054;0.880150;0.400354;,
  -0.179987;0.851765;0.492037;,
  -0.188650;0.783235;0.592414;,
  -0.275960;0.714705;0.642684;,
  -0.390777;0.686321;0.613398;;
  40;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  3;25,26,33;,
  3;26,27,33;,
  3;27,28,33;,
  3;28,29,33;,
  3;29,30,33;,
  3;30,31,33;,
  3;31,32,33;,
  3;32,25,33;,
  3;0,34,35;,
  3;0,36,34;,
  3;0,37,36;,
  3;0,38,37;,
  3;0,39,38;,
  3;0,40,39;,
  3;0,41,40;,
  3;0,35,41;;
 }
}
