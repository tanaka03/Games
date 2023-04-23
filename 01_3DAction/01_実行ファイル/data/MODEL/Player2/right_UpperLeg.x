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
 26;
 3.23383;0.04592;-0.23547;,
 0.18835;0.04592;-0.23547;,
 0.18835;0.04592;2.76047;,
 2.19987;0.04592;2.22309;,
 2.19987;0.04592;-2.92753;,
 0.18835;0.04592;-3.46494;,
 -2.80803;0.04592;-0.23547;,
 -1.77407;0.04592;2.22309;,
 -1.77407;0.04592;-2.92753;,
 2.28076;-10.41184;-0.25268;,
 0.19607;-10.41184;-0.25268;,
 0.19607;-10.41184;-3.00574;,
 1.57299;-10.41184;-2.54762;,
 1.57299;-10.41184;1.84319;,
 0.19607;-10.41184;2.30131;,
 -1.85496;-10.41184;-0.25268;,
 -1.14722;-10.41184;-2.54762;,
 -1.14722;-10.41184;1.84319;,
 -2.73365;-4.04767;-0.21663;,
 -1.72513;-4.04767;2.63875;,
 -1.72513;-4.04767;-3.34318;,
 0.18895;-4.04767;3.26288;,
 0.18895;-4.04767;-3.96731;,
 2.15093;-4.04767;2.63875;,
 2.15093;-4.04767;-3.34318;,
 3.15941;-4.04767;-0.21663;;
 
 24;
 4;0,1,2,3;,
 4;0,4,5,1;,
 4;1,6,7,2;,
 4;1,5,8,6;,
 4;9,10,11,12;,
 4;9,13,14,10;,
 4;10,15,16,11;,
 4;10,14,17,15;,
 4;18,19,7,6;,
 4;18,15,17,19;,
 4;18,20,16,15;,
 4;18,6,8,20;,
 4;19,21,2,7;,
 4;19,17,14,21;,
 4;20,22,11,16;,
 4;20,8,5,22;,
 4;21,23,3,2;,
 4;21,14,13,23;,
 4;22,24,12,11;,
 4;22,5,4,24;,
 4;23,25,0,3;,
 4;23,13,9,25;,
 4;24,25,9,12;,
 4;24,4,0,25;;
 
 MeshMaterialList {
  9;
  24;
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
  26;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.997680;-0.066614;0.014054;,
  -0.691238;-0.045981;0.721163;,
  -0.701386;-0.046370;-0.711271;,
  -0.003505;-0.020344;0.999787;,
  -0.003513;-0.020186;-0.999790;,
  0.688703;-0.045713;0.723601;,
  0.698888;-0.046277;-0.713732;,
  0.997680;-0.066616;0.014054;,
  -0.678889;0.060701;0.731727;,
  -0.999889;0.002335;0.014721;,
  -0.990844;-0.134352;0.013331;,
  -0.695536;-0.151935;0.702243;,
  -0.705077;-0.151297;-0.692803;,
  -0.689685;0.059353;-0.721673;,
  -0.003345;0.109749;0.993954;,
  -0.003607;-0.151247;0.988489;,
  -0.003623;-0.150928;-0.988538;,
  -0.003345;0.109744;-0.993954;,
  0.676432;0.060962;0.733978;,
  0.692959;-0.151679;0.704842;,
  0.702512;-0.151385;-0.695384;,
  0.687261;0.059618;-0.723960;,
  0.999889;0.002330;0.014720;,
  0.990844;-0.134351;0.013331;;
  24;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,3,10,11;,
  4;2,12,13,3;,
  4;2,4,14,12;,
  4;2,11,15,4;,
  4;3,5,16,10;,
  4;3,13,17,5;,
  4;4,6,18,14;,
  4;4,15,19,6;,
  4;5,7,20,16;,
  4;5,17,21,7;,
  4;6,8,22,18;,
  4;6,19,23,8;,
  4;7,9,24,20;,
  4;7,21,25,9;,
  4;8,9,25,22;,
  4;8,23,24,9;;
 }
}
