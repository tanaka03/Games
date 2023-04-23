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
 80;
 -0.03224;0.87539;-0.94304;,
 0.23621;0.65772;-1.69768;,
 0.16856;-1.32521;-1.69768;,
 -0.09990;-1.32521;-0.94304;,
 -0.21174;-1.32521;0.13827;,
 -0.14409;0.87539;0.13827;,
 -0.03224;0.87539;1.07599;,
 -0.09990;-1.32521;1.07599;,
 0.16856;-1.32521;1.63971;,
 0.23621;0.65772;1.63971;,
 1.10330;-0.95703;-1.96273;,
 1.00888;-1.10306;-0.99939;,
 1.01293;0.77330;-1.96273;,
 0.87168;1.17442;0.14857;,
 0.96209;-1.10306;0.14857;,
 1.00888;-1.10306;1.14412;,
 1.10330;-0.95703;1.90476;,
 1.01293;0.77330;1.90476;,
 1.92117;0.96204;-2.00761;,
 3.20275;0.90055;-2.01597;,
 3.24816;0.03438;-2.01597;,
 2.19268;-0.03827;-2.00761;,
 1.72536;1.17442;-0.99939;,
 3.68708;0.90055;-0.99939;,
 3.73253;0.03438;-0.99939;,
 1.99688;-0.38545;-0.99939;,
 1.73378;1.17442;0.14857;,
 3.85664;0.90055;0.14857;,
 3.90203;0.03438;0.14857;,
 2.00528;-0.38545;0.14857;,
 1.72536;1.17442;1.14412;,
 3.68708;0.90055;1.14412;,
 3.73253;0.03438;1.14412;,
 1.99688;-0.38545;1.14412;,
 1.67207;0.96204;1.94964;,
 3.20275;0.90055;1.95801;,
 3.24816;0.03438;1.95801;,
 1.94358;-0.23948;1.94964;,
 6.02147;0.82068;-1.98877;,
 6.04964;0.27869;-1.99278;,
 5.69732;0.27869;-2.32681;,
 5.66922;0.82068;-2.32280;,
 4.36978;0.82820;-1.44113;,
 4.40246;0.20494;-1.44113;,
 3.97309;0.82820;-2.07738;,
 4.00577;0.20494;-2.07738;,
 5.93567;0.89386;-0.35776;,
 5.82137;0.89386;-1.13189;,
 5.96634;0.30980;-0.35776;,
 5.85199;0.30980;-1.13189;,
 6.97944;0.84045;-0.59611;,
 6.90078;0.84045;-1.12866;,
 7.00051;0.43864;-0.59611;,
 6.92186;0.43864;-1.12866;,
 5.84677;0.29166;1.13933;,
 5.81425;0.91172;1.13933;,
 5.96814;0.29166;0.42655;,
 5.93563;0.91172;0.42655;,
 6.80049;0.36753;1.19030;,
 6.77217;0.90686;1.19030;,
 6.90605;0.36753;0.57044;,
 6.87771;0.90686;0.57044;,
 4.75878;0.79418;2.16842;,
 5.04284;0.79418;1.69115;,
 4.78543;0.28622;2.16842;,
 5.06949;0.28622;1.69115;,
 5.12192;0.72815;2.17877;,
 5.31440;0.72815;1.85530;,
 5.13993;0.38384;2.17877;,
 5.33246;0.38384;1.85530;,
 0.54898;-0.83597;-2.21484;,
 1.21144;-0.50952;-2.64588;,
 0.58154;0.43907;-2.21484;,
 1.16415;0.63909;-2.64588;,
 1.95725;-0.24408;-2.96292;,
 1.87300;0.63207;-2.96292;,
 2.92783;0.77302;-3.57848;,
 2.99683;0.28398;-3.50267;,
 2.96724;1.04332;-3.18037;,
 3.18968;0.45256;-3.18037;;
 
 80;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;6,5,4,7;,
 4;6,7,8,9;,
 4;10,11,3,2;,
 4;12,1,0,13;,
 4;11,14,4,3;,
 4;14,15,7,4;,
 4;15,16,8,7;,
 4;13,6,9,17;,
 4;16,17,9,8;,
 4;18,19,20,21;,
 4;18,12,13,22;,
 4;18,22,23,19;,
 4;21,20,24,25;,
 4;21,25,11,10;,
 4;22,26,27,23;,
 4;25,24,28,29;,
 4;25,29,14,11;,
 4;26,30,31,27;,
 4;29,28,32,33;,
 4;29,33,15,14;,
 4;30,13,17,34;,
 4;30,34,35,31;,
 4;33,32,36,37;,
 4;33,37,16,15;,
 4;34,17,16,37;,
 4;34,37,36,35;,
 4;38,39,40,41;,
 4;42,23,24,43;,
 4;42,43,39,38;,
 4;42,38,41,44;,
 4;42,44,19,23;,
 4;43,24,20,45;,
 4;43,45,40,39;,
 4;44,41,40,45;,
 4;44,45,20,19;,
 4;46,47,23,27;,
 4;48,46,27,28;,
 4;49,48,28,24;,
 4;47,49,24,23;,
 4;50,51,47,46;,
 4;52,50,46,48;,
 4;53,52,48,49;,
 4;51,53,49,47;,
 4;51,50,52,53;,
 4;54,55,31,32;,
 4;56,54,32,28;,
 4;57,56,28,27;,
 4;55,57,27,31;,
 4;58,59,55,54;,
 4;60,58,54,56;,
 4;61,60,56,57;,
 4;59,61,57,55;,
 4;59,58,60,61;,
 4;62,63,31,35;,
 4;64,62,35,36;,
 4;65,64,36,32;,
 4;63,65,32,31;,
 4;66,67,63,62;,
 4;68,66,62,64;,
 4;69,68,64,65;,
 4;67,69,65,63;,
 4;67,66,68,69;,
 4;70,71,10,2;,
 4;72,70,2,1;,
 4;73,72,1,12;,
 4;71,70,72,73;,
 4;71,74,21,10;,
 4;75,73,12,18;,
 4;75,74,71,73;,
 4;76,77,74,75;,
 4;78,76,75,18;,
 4;79,78,18,21;,
 4;77,79,21,74;,
 4;77,76,78,79;,
 3;13,0,5;,
 3;13,26,22;,
 3;13,5,6;,
 3;13,30,26;;
 
 MeshMaterialList {
  9;
  80;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.656000;0.527200;0.370400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.759200;0.708800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.132000;0.091200;0.068800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.339200;0.304000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.091200;0.119200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.870000;0.870000;0.870000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.060000;0.060000;0.060000;;
  }
  Material {
   0.800000;0.684000;0.696800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.700000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  105;
  -0.807185;0.327433;-0.491162;,
  -0.888884;0.027737;-0.457292;,
  -0.043577;-0.002647;-0.999047;,
  0.075748;0.991665;0.104227;,
  0.183253;-0.974942;0.126120;,
  -0.653488;0.013920;0.756809;,
  -0.999497;0.030727;0.007818;,
  0.066165;0.997809;0.000043;,
  0.175181;-0.984536;0.001073;,
  -0.974470;0.030758;-0.222400;,
  0.077932;0.995853;-0.046941;,
  0.174816;-0.980549;-0.089236;,
  -0.959506;0.030269;0.280058;,
  0.070001;0.996039;0.054836;,
  0.178605;-0.981196;0.073169;,
  0.387560;-0.894436;-0.223117;,
  -0.228865;0.929967;-0.287719;,
  0.421900;-0.906298;-0.024978;,
  0.393106;-0.919493;-0.000907;,
  0.421357;-0.906326;0.032100;,
  -0.162423;0.986678;0.009192;,
  0.448253;-0.890532;0.077607;,
  -0.185368;0.946964;0.262484;,
  -0.007251;-0.001104;-0.999973;,
  -0.003004;0.995798;-0.091532;,
  0.402655;-0.911549;-0.083353;,
  0.066701;0.997773;0.000382;,
  0.409116;-0.912483;0.000289;,
  -0.014534;0.994349;0.105157;,
  0.417629;-0.905316;0.077394;,
  -0.096798;0.974100;0.204349;,
  0.423891;-0.893141;0.150385;,
  0.301819;0.020661;-0.953141;,
  0.687476;0.041046;-0.725046;,
  0.434110;0.020960;0.900616;,
  0.043215;0.998778;-0.023995;,
  0.115509;-0.990989;-0.067817;,
  0.026280;0.999647;-0.003881;,
  0.229919;0.012061;0.973135;,
  0.123640;-0.992159;-0.018260;,
  0.049441;0.998750;-0.007301;,
  0.223186;0.011710;0.974706;,
  0.119596;-0.992665;-0.017664;,
  0.141755;0.007436;-0.989874;,
  0.099725;-0.994870;0.016981;,
  -0.025458;-0.001336;0.999675;,
  0.151009;0.007926;-0.988501;,
  0.078584;-0.996818;0.013382;,
  -0.053147;-0.002789;0.998583;,
  0.119341;0.990310;0.071022;,
  -0.081731;-0.004285;0.996645;,
  0.204104;-0.971383;0.121479;,
  0.175067;0.979028;0.104185;,
  -0.028759;-0.001507;0.999585;,
  0.258152;-0.953808;0.153650;,
  -0.669827;0.314607;-0.672573;,
  0.091990;-0.803526;-0.588120;,
  0.311456;-0.869918;-0.382411;,
  -0.458327;0.517462;-0.722613;,
  -0.283597;0.898245;-0.335751;,
  0.506015;-0.862316;-0.018992;,
  -0.390840;0.833936;-0.389608;,
  0.703395;0.226730;0.673669;,
  -0.460079;-0.121617;-0.879509;,
  0.230999;-0.972950;-0.002685;,
  0.190417;-0.928384;-0.319130;,
  -0.099517;0.966581;-0.236258;,
  -0.192609;0.972084;-0.133997;,
  0.191447;-0.981502;-0.001055;,
  0.229685;-0.973261;0.002919;,
  0.267391;-0.963347;0.021560;,
  -0.189083;0.968057;0.164659;,
  -0.090695;0.952311;0.291338;,
  -0.179351;-0.006151;0.983766;,
  -0.180594;0.948684;-0.259584;,
  0.087460;0.992226;-0.088530;,
  0.452483;-0.887146;-0.090729;,
  0.171882;-0.972005;-0.160197;,
  -0.031698;-0.004669;0.999487;,
  -0.070347;-0.003929;0.997515;,
  0.545170;0.028594;0.837837;,
  0.315958;0.012984;0.948684;,
  0.003724;0.999988;-0.003050;,
  0.036465;-0.998889;-0.029861;,
  -0.112259;-0.004035;-0.993671;,
  0.236640;0.012412;0.971518;,
  -0.029500;-0.001547;-0.999564;,
  -0.061973;-0.003250;-0.998073;,
  0.003004;0.000158;-0.999995;,
  0.987940;0.051821;-0.145911;,
  0.002252;0.000118;0.999997;,
  0.132488;0.006945;-0.991160;,
  -0.000112;1.000000;-0.000019;,
  0.005029;0.999987;0.000856;,
  0.984490;0.051709;0.167646;,
  0.450231;0.023620;-0.892600;,
  0.375435;0.019696;-0.926639;,
  0.521979;0.027385;-0.852519;,
  0.858466;0.044983;0.510894;,
  -0.707722;0.009861;-0.706422;,
  -0.486073;-0.016431;-0.873764;,
  -0.429495;-0.074736;-0.899972;,
  0.503154;-0.858071;0.102714;,
  0.883417;0.189410;-0.428601;,
  -0.282425;0.959287;0.002267;;
  80;
  4;9,0,1,9;,
  4;9,9,6,6;,
  4;12,6,6,12;,
  4;12,12,5,5;,
  4;15,17,64,65;,
  4;16,66,67,20;,
  4;17,18,68,64;,
  4;18,19,69,68;,
  4;19,21,70,69;,
  4;20,71,72,22;,
  4;73,73,5,5;,
  4;23,2,2,23;,
  4;74,16,20,24;,
  4;74,24,10,75;,
  4;76,77,11,25;,
  4;76,25,17,15;,
  4;24,26,7,10;,
  4;25,11,8,27;,
  4;25,27,18,17;,
  4;26,28,13,7;,
  4;27,8,14,29;,
  4;27,29,19,18;,
  4;28,20,22,30;,
  4;28,30,3,13;,
  4;29,14,4,31;,
  4;29,31,21,19;,
  4;78,73,73,78;,
  4;78,78,79,79;,
  4;33,33,32,32;,
  4;34,80,80,34;,
  4;34,34,81,81;,
  4;35,82,82,35;,
  4;35,35,75,10;,
  4;36,11,77,36;,
  4;36,36,83,83;,
  4;84,32,32,84;,
  4;84,84,2,2;,
  4;37,37,10,7;,
  4;38,38,85,85;,
  4;39,39,8,11;,
  4;86,86,87,87;,
  4;40,40,37,37;,
  4;41,41,38,38;,
  4;42,42,39,39;,
  4;88,88,86,86;,
  4;89,89,89,89;,
  4;45,45,90,90;,
  4;44,44,14,8;,
  4;43,43,91,91;,
  4;92,92,7,13;,
  4;48,48,45,45;,
  4;47,47,44,44;,
  4;46,46,43,43;,
  4;93,93,92,92;,
  4;94,94,94,94;,
  4;49,49,13,3;,
  4;50,50,79,79;,
  4;51,51,4,14;,
  4;95,95,96,96;,
  4;52,52,49,49;,
  4;53,53,50,50;,
  4;54,54,51,51;,
  4;97,97,95,95;,
  4;98,98,98,98;,
  4;56,57,15,65;,
  4;55,99,1,0;,
  4;58,55,0,16;,
  4;100,99,55,58;,
  4;57,60,76,15;,
  4;59,58,16,74;,
  4;101,101,100,58;,
  4;63,63,101,101;,
  4;61,61,59,74;,
  4;62,62,62,62;,
  4;102,102,76,60;,
  4;103,103,103,103;,
  3;20,67,104;,
  3;20,26,24;,
  3;20,104,71;,
  3;20,28,26;;
 }
}
