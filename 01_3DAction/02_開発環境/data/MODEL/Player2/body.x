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
 248;
 3.82213;9.17400;-8.89769;,
 8.20078;9.17400;-4.27849;,
 7.37806;4.49853;-3.89103;,
 3.43481;4.49853;-7.69371;,
 3.82213;9.17400;7.73628;,
 3.43481;4.49853;6.92897;,
 7.37806;4.49853;3.14392;,
 8.20078;9.17400;3.53327;,
 -4.58827;9.17400;-8.89769;,
 -4.13924;4.49853;-7.69371;,
 -7.52343;4.49853;-3.89103;,
 -8.34614;9.17400;-4.27849;,
 -4.58827;9.17400;7.73628;,
 -8.34614;9.17400;3.53327;,
 -7.52343;4.49853;3.14392;,
 -4.13924;4.49853;6.92897;,
 -3.83824;2.55844;-7.40771;,
 3.17520;2.55844;-7.40771;,
 2.74372;0.67648;-7.04052;,
 -3.33795;0.67648;-7.04052;,
 -6.05536;0.67648;-3.87361;,
 -6.97195;2.55844;-3.75379;,
 6.82657;2.55844;-3.75379;,
 5.90999;0.67648;-3.43265;,
 -6.97195;2.55844;3.00599;,
 -6.05536;0.67648;3.12636;,
 -3.33795;0.67648;6.89258;,
 -3.83824;2.55844;6.64295;,
 6.82657;2.55844;3.00599;,
 3.17520;2.55844;6.64295;,
 2.74372;0.67648;6.89258;,
 5.90999;0.67648;2.68540;,
 -4.80628;13.50378;-8.89769;,
 -3.18199;16.97163;-7.19110;,
 2.51787;16.97163;-7.19110;,
 4.01021;13.50378;-8.89769;,
 -8.74560;13.50378;-4.27849;,
 -6.33002;17.17628;-3.78639;,
 6.18464;17.17628;-3.78639;,
 8.60022;13.50378;-4.27849;,
 -8.74560;13.50378;3.53327;,
 -4.80628;13.50378;7.73628;,
 -3.49666;17.11864;6.94353;,
 -6.33002;17.11864;4.33155;,
 8.60022;13.50378;3.53327;,
 6.18464;17.11864;4.33155;,
 2.83258;17.11864;6.94353;,
 4.01021;13.50378;7.73628;,
 2.54516;17.74790;-5.64291;,
 6.84102;17.93479;-1.96161;,
 -3.20928;17.74790;-5.64291;,
 -6.98638;17.93479;-1.96161;,
 2.37390;-0.33714;-6.39522;,
 -2.96812;-0.33714;-6.39522;,
 2.80594;17.91746;5.77660;,
 6.84102;17.93479;1.57482;,
 -3.47002;17.91746;5.77660;,
 -6.98638;17.93479;1.57482;,
 2.37390;-0.33714;5.66061;,
 -2.96812;-0.33714;5.66061;,
 -0.38240;13.51914;-11.71538;,
 -0.38240;18.11144;-8.06478;,
 8.46021;18.00127;-5.25027;,
 9.13342;13.21890;-7.24089;,
 -9.08773;13.21890;-7.24089;,
 -8.38751;18.00127;-4.67733;,
 9.13342;13.21890;7.76724;,
 7.16998;18.00127;5.99137;,
 -0.38240;18.11144;8.89189;,
 -0.38240;13.31543;9.66586;,
 -9.08773;13.21890;7.76724;,
 -7.19340;18.00127;5.93669;,
 -0.38240;9.65628;-12.23612;,
 7.59489;7.16033;-7.21830;,
 -7.61837;7.16033;-7.59170;,
 7.95392;7.16033;7.44073;,
 -0.38240;7.23952;9.66586;,
 -7.64126;7.16033;6.27589;,
 -9.42642;13.21890;-1.33571;,
 -8.73934;7.16033;-1.00763;,
 -7.91769;18.00127;-0.50108;,
 -0.38240;18.11144;-1.43415;,
 7.95255;18.00127;-0.82709;,
 9.13342;13.21890;-1.33571;,
 8.23173;7.16033;-1.00763;,
 -0.34338;4.77493;-9.90798;,
 7.35023;4.05069;-7.14263;,
 -7.42990;4.05069;-7.14263;,
 7.79065;4.05069;-1.76348;,
 -8.07109;4.05069;-1.76348;,
 7.59854;4.05069;6.55316;,
 -7.44572;4.05069;5.69794;,
 -0.34338;4.10551;8.49421;,
 -6.98928;3.20823;-6.04946;,
 -0.29267;4.31423;-9.38168;,
 -0.41254;-5.06895;-13.22140;,
 -9.06725;-5.06895;-9.59814;,
 -13.01188;-5.06895;-4.12749;,
 -7.41321;3.20823;-1.23908;,
 6.89656;3.20823;-6.04946;,
 8.94387;-5.06895;-9.59814;,
 -9.06725;-5.06895;6.38106;,
 -6.99971;3.20823;5.43769;,
 7.18777;3.20823;-1.23908;,
 12.58319;-5.06895;-4.12749;,
 -0.41254;-5.06895;12.22042;,
 -0.29267;3.24445;7.62656;,
 7.06073;3.20823;6.01453;,
 8.94387;-5.06895;6.38106;,
 -10.28727;-4.40887;-3.35530;,
 -7.18245;-4.40887;-7.66125;,
 -0.37033;-4.40887;-10.51310;,
 -0.35692;-4.40887;-2.53011;,
 -0.37033;-4.40887;9.51214;,
 -7.18245;-4.40887;4.91596;,
 6.99408;-4.40887;-7.66125;,
 9.85856;-4.40887;-3.35530;,
 6.99408;-4.40887;4.91596;,
 -0.44893;-16.08510;-15.55812;,
 10.62613;-16.08510;-11.26928;,
 -10.69343;-16.08510;-11.26928;,
 14.93400;-16.08510;-4.79374;,
 -15.36270;-16.08510;-4.79374;,
 10.62613;-16.08510;7.64513;,
 -10.69343;-16.08510;7.64513;,
 -0.44893;-16.08510;14.55713;,
 -0.43902;-17.78872;-14.92154;,
 10.16785;-17.78872;-10.81405;,
 -10.25045;-17.78872;-10.81405;,
 14.29357;-17.78872;-4.61222;,
 -14.72225;-17.78872;-4.61222;,
 10.16785;-17.78872;7.30080;,
 -10.25045;-17.78872;7.30080;,
 -0.43902;-17.78872;13.92058;,
 7.83799;2.80920;-0.47392;,
 7.98756;3.88219;-0.47392;,
 6.76729;3.88219;-6.20158;,
 6.64557;2.80920;-6.12734;,
 9.00768;4.65258;-0.47392;,
 7.54875;4.65258;-6.83796;,
 8.97078;1.86057;-0.47392;,
 7.51335;1.86057;-6.83399;,
 1.32829;3.88219;-9.24919;,
 1.27707;2.80920;-9.13547;,
 1.50547;4.65258;-10.22420;,
 0.91510;1.86057;-10.70208;,
 -4.85668;3.88219;-8.19078;,
 -4.82775;2.80920;-8.09074;,
 -5.36676;4.65258;-9.04817;,
 -5.39414;1.86057;-9.04287;,
 -8.43769;3.88219;-3.52151;,
 -8.35645;2.80920;-3.48202;,
 -9.39633;4.65258;-3.86016;,
 -9.42096;1.86057;-3.85805;,
 -8.13725;3.88219;2.57369;,
 -8.05601;2.80920;2.53419;,
 -9.09590;4.65258;2.91234;,
 -9.35213;1.86057;2.91022;,
 -4.85668;3.88219;7.24295;,
 -4.82775;2.80920;7.14290;,
 -5.36676;4.65258;8.10033;,
 -5.39414;1.86057;8.09505;,
 1.32829;3.88219;8.30135;,
 1.27707;2.80920;8.18761;,
 1.50547;4.65258;9.27636;,
 1.47377;1.86057;9.27029;,
 6.75448;3.54708;5.84541;,
 6.63275;2.47407;5.77116;,
 7.53598;4.31747;6.48179;,
 7.50054;1.52547;6.47782;,
 -6.39133;4.27059;-7.08278;,
 -6.03440;3.93489;-7.85605;,
 -6.50882;3.93489;-8.70292;,
 -7.34978;4.27059;-8.67042;,
 -7.80718;3.93489;-7.95778;,
 -7.21044;3.93489;-6.93415;,
 -6.29423;1.74646;-7.07881;,
 -7.32267;2.08217;-6.89380;,
 -7.90183;2.08217;-7.83419;,
 -7.44689;1.74646;-8.67439;,
 -6.42255;2.08217;-8.77653;,
 -5.91384;2.08217;-7.94639;,
 -7.64601;2.96575;-9.25104;,
 -6.61066;2.97711;-9.17532;,
 -8.05472;2.97711;-8.17789;,
 -5.72572;2.97711;-7.54759;,
 -7.16976;2.97711;-6.55015;,
 -6.01905;2.96575;-6.32063;,
 -5.42872;5.03139;-9.63000;,
 -6.33255;3.89151;-8.18335;,
 -5.79479;3.89151;-7.22782;,
 -4.29317;5.03139;-7.61214;,
 -5.42872;0.02994;-9.63000;,
 -4.29317;0.02994;-7.61214;,
 -5.79479;1.27681;-7.22782;,
 -6.33255;1.27681;-8.18335;,
 -3.44910;6.33584;-11.07290;,
 -2.36392;6.33584;-9.14448;,
 -1.20733;6.00431;-9.98853;,
 -2.32110;6.00431;-11.96781;,
 -3.44910;-1.27459;-11.07290;,
 -2.32110;-0.94306;-11.96781;,
 -1.20733;-0.94306;-9.98853;,
 -2.36392;-1.27459;-9.14448;,
 -0.35825;4.73700;-10.59450;,
 -0.88839;4.73700;-11.91228;,
 -0.88839;0.32425;-11.91228;,
 -0.35825;0.32425;-10.59450;,
 -5.42872;2.49518;-9.63000;,
 -6.43721;2.50720;-8.00761;,
 -3.86540;2.47667;-11.81270;,
 -5.89948;2.50720;-7.05208;,
 -2.32110;2.48137;-11.96781;,
 -4.29317;2.49518;-7.61214;,
 -0.88839;2.49938;-11.91228;,
 -2.14100;2.47667;-8.74840;,
 -0.35825;2.49938;-10.59450;,
 -1.20733;2.48137;-9.98853;,
 -7.73540;5.03139;-4.99852;,
 -7.06897;3.89151;-6.56873;,
 -7.74957;3.89151;-7.42842;,
 -9.17259;5.03139;-6.81394;,
 -7.73540;0.02994;-4.99852;,
 -9.17259;0.02994;-6.81394;,
 -7.74957;1.27681;-7.42842;,
 -7.06897;1.27681;-6.56873;,
 -9.46489;6.33584;-3.26372;,
 -10.83840;6.33584;-4.99860;,
 -11.84868;6.00431;-3.98404;,
 -10.43901;6.00431;-2.20341;,
 -9.46489;-1.27459;-3.26372;,
 -10.43901;-0.94306;-2.20341;,
 -11.84868;-0.94306;-3.98404;,
 -10.83840;-1.27459;-4.99860;,
 -12.59252;4.73700;-3.25268;,
 -11.86278;4.73700;-2.03409;,
 -11.86278;0.32425;-2.03409;,
 -12.59252;0.32425;-3.25268;,
 -7.73540;2.49518;-4.99852;,
 -6.99307;2.50720;-6.75871;,
 -8.93799;2.47667;-2.59815;,
 -7.67369;2.50720;-7.61839;,
 -10.43901;2.48137;-2.20341;,
 -9.17259;2.49518;-6.81394;,
 -11.86278;2.49938;-2.03409;,
 -11.12052;2.47667;-5.35496;,
 -12.59252;2.49938;-3.25268;,
 -11.84868;2.48137;-3.98404;;
 
 242;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,0,3,9;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,15,5,4;,
 4;16,9,3,17;,
 4;16,17,18,19;,
 4;16,19,20,21;,
 4;16,21,10,9;,
 4;17,3,2,22;,
 4;17,22,23,18;,
 4;24,25,26,27;,
 4;24,27,15,14;,
 4;28,6,5,29;,
 4;28,29,30,31;,
 4;27,26,30,29;,
 4;27,29,5,15;,
 4;32,33,34,35;,
 4;32,35,0,8;,
 4;32,8,11,36;,
 4;32,36,37,33;,
 4;35,34,38,39;,
 4;35,39,1,0;,
 4;40,13,12,41;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;44,47,4,7;,
 4;41,12,4,47;,
 4;41,47,46,42;,
 4;48,49,38,34;,
 4;48,34,33,50;,
 4;50,33,37,51;,
 4;52,53,19,18;,
 4;54,46,45,55;,
 4;54,55,49,48;,
 4;54,48,50,56;,
 4;54,56,42,46;,
 4;55,44,39,49;,
 4;56,50,51,57;,
 4;56,57,43,42;,
 4;44,7,1,39;,
 4;57,51,36,40;,
 4;7,6,2,1;,
 4;40,36,11,13;,
 4;6,28,22,2;,
 4;13,11,10,14;,
 4;28,31,23,22;,
 4;14,10,21,24;,
 4;31,58,52,23;,
 4;24,21,20,25;,
 4;58,30,26,59;,
 4;58,59,53,52;,
 4;25,20,53,59;,
 3;44,55,45;,
 3;39,38,49;,
 3;31,30,58;,
 3;23,52,18;,
 3;36,51,37;,
 3;20,19,53;,
 3;40,43,57;,
 3;25,59,26;,
 4;60,61,62,63;,
 4;60,64,65,61;,
 4;66,67,68,69;,
 4;70,69,68,71;,
 4;72,60,63,73;,
 4;72,74,64,60;,
 4;75,66,69,76;,
 4;77,76,69,70;,
 4;78,64,74,79;,
 4;78,79,77,70;,
 4;78,70,71,80;,
 4;78,80,65,64;,
 4;80,71,68,81;,
 4;80,81,61,65;,
 4;81,68,67,82;,
 4;81,82,62,61;,
 4;82,67,66,83;,
 4;82,83,63,62;,
 4;83,66,75,84;,
 4;83,84,73,63;,
 4;85,72,73,86;,
 4;85,87,74,72;,
 4;86,73,84,88;,
 4;87,89,79,74;,
 4;88,84,75,90;,
 4;89,91,77,79;,
 4;90,75,76,92;,
 4;91,92,76,77;,
 4;93,87,85,94;,
 4;93,94,95,96;,
 4;93,96,97,98;,
 4;93,98,89,87;,
 4;94,85,86,99;,
 4;94,99,100,95;,
 4;98,97,101,102;,
 4;98,102,91,89;,
 4;99,86,88,103;,
 4;99,103,104,100;,
 4;102,101,105,106;,
 4;102,106,92,91;,
 4;103,88,90,107;,
 4;103,107,108,104;,
 4;106,105,108,107;,
 4;106,107,90,92;,
 4;109,110,111,112;,
 4;109,112,113,114;,
 4;112,111,115,116;,
 4;112,116,117,113;,
 4;118,95,100,119;,
 4;118,120,96,95;,
 4;119,100,104,121;,
 4;120,122,97,96;,
 4;121,104,108,123;,
 4;122,124,101,97;,
 4;123,108,105,125;,
 4;124,125,105,101;,
 4;126,118,119,127;,
 4;126,127,115,111;,
 4;126,111,110,128;,
 4;126,128,120,118;,
 4;127,119,121,129;,
 4;127,129,116,115;,
 4;128,110,109,130;,
 4;128,130,122,120;,
 4;129,121,123,131;,
 4;129,131,117,116;,
 4;130,109,114,132;,
 4;130,132,124,122;,
 4;131,123,125,133;,
 4;131,133,113,117;,
 4;132,114,113,133;,
 4;132,133,125,124;,
 4;134,135,136,137;,
 4;135,138,139,136;,
 4;138,140,141,139;,
 4;140,134,137,141;,
 4;137,136,142,143;,
 4;136,139,144,142;,
 4;139,141,145,144;,
 4;141,137,143,145;,
 4;143,142,146,147;,
 4;142,144,148,146;,
 4;144,145,149,148;,
 4;145,143,147,149;,
 4;147,146,150,151;,
 4;146,148,152,150;,
 4;148,149,153,152;,
 4;149,147,151,153;,
 4;151,150,154,155;,
 4;150,152,156,154;,
 4;152,153,157,156;,
 4;153,151,155,157;,
 4;155,154,158,159;,
 4;154,156,160,158;,
 4;156,157,161,160;,
 4;157,155,159,161;,
 4;159,158,162,163;,
 4;158,160,164,162;,
 4;160,161,165,164;,
 4;161,159,163,165;,
 4;163,162,166,167;,
 4;162,164,168,166;,
 4;164,165,169,168;,
 4;165,163,167,169;,
 4;167,166,135,134;,
 4;166,168,138,135;,
 4;168,169,140,138;,
 4;169,167,134,140;,
 4;170,171,172,173;,
 4;170,173,174,175;,
 4;176,177,178,179;,
 4;176,179,180,181;,
 4;182,173,172,183;,
 4;182,183,180,179;,
 4;182,179,178,184;,
 4;182,184,174,173;,
 4;183,172,171,185;,
 4;183,185,181,180;,
 4;184,178,177,186;,
 4;184,186,175,174;,
 4;185,171,170,187;,
 4;185,187,176,181;,
 4;186,177,176,187;,
 4;186,187,170,175;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,188,191,197;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;200,203,193,192;,
 4;204,205,199,198;,
 4;206,207,202,201;,
 4;208,192,195,209;,
 4;208,209,189,188;,
 4;208,188,196,210;,
 4;208,210,200,192;,
 4;209,195,194,211;,
 4;209,211,190,189;,
 4;210,196,199,212;,
 4;210,212,201,200;,
 4;211,194,193,213;,
 4;211,213,191,190;,
 4;212,199,205,214;,
 4;212,214,206,201;,
 4;213,193,203,215;,
 4;213,215,197,191;,
 4;214,205,204,216;,
 4;214,216,207,206;,
 4;215,203,202,217;,
 4;215,217,198,197;,
 4;216,204,198,217;,
 4;216,217,202,207;,
 4;218,219,220,221;,
 4;222,223,224,225;,
 4;226,218,221,227;,
 4;226,227,228,229;,
 4;230,231,232,233;,
 4;230,233,223,222;,
 4;234,235,229,228;,
 4;236,237,232,231;,
 4;238,222,225,239;,
 4;238,239,219,218;,
 4;238,218,226,240;,
 4;238,240,230,222;,
 4;239,225,224,241;,
 4;239,241,220,219;,
 4;240,226,229,242;,
 4;240,242,231,230;,
 4;241,224,223,243;,
 4;241,243,221,220;,
 4;242,229,235,244;,
 4;242,244,236,231;,
 4;243,223,233,245;,
 4;243,245,227,221;,
 4;244,235,234,246;,
 4;244,246,237,236;,
 4;245,233,232,247;,
 4;245,247,228,227;,
 4;246,234,228,247;,
 4;246,247,232,237;;
 
 MeshMaterialList {
  9;
  242;
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
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
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
  318;
  -0.590126;0.630002;-0.504826;,
  -0.930234;-0.140305;-0.339087;,
  0.562770;0.637554;-0.526132;,
  0.916694;-0.140130;-0.374213;,
  0.636529;0.565761;0.524162;,
  0.910444;-0.133442;0.391515;,
  -0.664309;0.560792;0.494171;,
  -0.924662;-0.134282;0.356327;,
  -0.910939;-0.235124;-0.338979;,
  0.897330;-0.234680;-0.373798;,
  0.895953;-0.228357;0.380948;,
  -0.909757;-0.229458;0.345963;,
  -0.708601;-0.628905;-0.319943;,
  0.688352;-0.646858;-0.328248;,
  0.687350;-0.664447;0.293359;,
  -0.708931;-0.646232;0.282491;,
  0.253126;0.718340;-0.648008;,
  0.384367;-0.136890;-0.912975;,
  0.275075;0.603516;0.748400;,
  0.371906;-0.220689;-0.901655;,
  0.368103;-0.106632;0.923650;,
  0.354358;-0.451071;-0.819125;,
  0.366980;-0.191884;0.910223;,
  0.380436;-0.479139;0.791008;,
  -0.278985;0.718872;-0.636703;,
  -0.418507;-0.141427;-0.897134;,
  -0.305409;0.607982;0.732859;,
  -0.404882;-0.228053;-0.885473;,
  -0.402727;-0.111276;0.908531;,
  -0.369224;-0.441693;-0.817668;,
  -0.400279;-0.199450;0.894425;,
  -0.398597;-0.469683;0.787729;,
  -0.398418;-0.241005;-0.884974;,
  0.370254;-0.246951;-0.895504;,
  -0.881412;-0.333289;-0.334712;,
  0.867257;-0.345401;-0.358556;,
  -0.891543;-0.309672;0.330536;,
  0.877652;-0.320664;0.356233;,
  -0.417326;-0.130863;0.899285;,
  0.388643;-0.137313;0.911099;,
  -0.394482;0.261371;-0.880948;,
  0.363297;0.254221;-0.896319;,
  -0.884920;0.282683;-0.370144;,
  0.872944;0.282919;-0.397399;,
  -0.902673;0.227871;0.365044;,
  0.891098;0.224323;0.394491;,
  -0.384357;0.140354;0.912453;,
  0.350521;0.130294;0.927447;,
  0.084644;0.967425;-0.238587;,
  0.563887;0.781696;-0.266425;,
  -0.098180;0.965856;-0.239756;,
  -0.576867;0.772429;-0.265665;,
  0.256368;-0.880953;-0.397741;,
  -0.268940;-0.877889;-0.396210;,
  0.091375;0.962198;0.256565;,
  0.603179;0.767245;0.217967;,
  -0.106185;0.960700;0.256476;,
  -0.616656;0.757144;0.215564;,
  0.225374;-0.931584;0.285232;,
  -0.239044;-0.928701;0.283501;,
  -0.219016;0.872901;-0.435976;,
  -0.631823;0.345151;-0.694025;,
  0.324213;0.494814;-0.806253;,
  0.635031;0.344074;-0.691628;,
  0.272901;0.281532;0.919927;,
  0.750969;0.278872;0.598561;,
  -0.301172;0.286150;0.909623;,
  -0.755420;0.285963;0.589547;,
  -0.013657;0.887514;-0.460579;,
  -0.014757;0.296315;0.954976;,
  -0.013136;0.317672;-0.948110;,
  -0.022780;0.292194;0.956088;,
  -0.020133;0.298398;-0.954229;,
  0.409517;0.254073;-0.876209;,
  -0.446366;0.285186;-0.848190;,
  0.253157;0.119815;0.959977;,
  -0.316731;0.073841;0.945637;,
  -0.031773;0.101160;0.994363;,
  -0.007157;-0.136172;-0.990659;,
  0.692744;-0.123743;-0.710489;,
  -0.805014;-0.156920;-0.572127;,
  0.231626;-0.181523;0.955719;,
  -0.349011;-0.201334;0.915235;,
  -0.062410;-0.200136;0.977778;,
  -0.998218;0.056147;0.020232;,
  -0.987476;-0.157365;-0.011251;,
  -0.958553;0.280783;0.048347;,
  -0.935554;0.340127;-0.095146;,
  -0.000689;0.999999;0.000782;,
  0.013314;0.999911;0.000752;,
  0.939513;0.329366;-0.093986;,
  0.999338;0.030559;0.019763;,
  0.988277;-0.150684;-0.024552;,
  -0.002127;-0.565443;-0.824785;,
  0.517631;-0.604317;-0.605689;,
  -0.682928;-0.526776;-0.506080;,
  0.935608;-0.351995;-0.027159;,
  -0.930454;-0.366195;-0.012556;,
  0.933697;-0.357333;0.022888;,
  -0.720110;-0.443900;0.533287;,
  -0.067499;-0.476465;0.876598;,
  -0.526943;-0.761136;-0.378158;,
  -0.003605;-0.787405;-0.616425;,
  -0.890577;0.450375;-0.063524;,
  0.542759;-0.751171;-0.375705;,
  -0.985064;-0.099713;0.140378;,
  0.954955;-0.293613;0.043044;,
  -0.048914;-0.168847;0.984428;,
  0.987442;-0.123728;0.098231;,
  0.000000;-1.000000;-0.000000;,
  -0.013442;-0.075039;-0.997090;,
  0.623714;-0.075259;-0.778021;,
  -0.619800;-0.074176;-0.781246;,
  0.989318;-0.077477;-0.123481;,
  -0.988573;-0.077698;-0.129175;,
  0.779918;-0.068327;0.622141;,
  -0.783162;-0.066993;0.618198;,
  0.528371;-0.063859;0.846608;,
  -0.012616;-0.350052;-0.936645;,
  0.585013;-0.352554;-0.730387;,
  0.590626;-0.310898;0.744650;,
  0.925839;-0.360211;-0.114322;,
  0.938626;-0.322597;0.122118;,
  0.740893;-0.318789;0.591143;,
  0.753777;-0.278895;-0.595011;,
  0.505151;-0.299484;0.809402;,
  -0.998596;0.030270;-0.043481;,
  -0.980631;-0.166033;0.103905;,
  -0.993041;0.082023;0.084510;,
  -0.940826;0.331376;0.070970;,
  -0.973034;0.229240;0.025561;,
  -0.014692;0.999892;0.000811;,
  -0.015295;0.999883;0.000811;,
  -0.000725;1.000000;0.000782;,
  0.013846;0.999904;0.000752;,
  0.012782;0.999918;0.000752;,
  0.967972;0.244773;0.055834;,
  0.950758;0.304874;0.055784;,
  0.996898;0.069445;0.037030;,
  0.999964;-0.008025;0.002618;,
  0.981402;0.183715;0.055665;,
  0.988112;-0.152163;0.021937;,
  0.978605;-0.199444;-0.050534;,
  0.990999;-0.097856;-0.091350;,
  0.203978;-0.494212;0.845073;,
  -0.639360;0.478187;-0.602126;,
  -0.012899;0.424966;-0.905117;,
  -0.821997;-0.569386;-0.010998;,
  0.642990;0.473498;-0.601967;,
  0.819379;0.496331;-0.286833;,
  -0.393205;-0.124608;0.910968;,
  0.366748;0.322999;0.872449;,
  0.167444;-0.654885;0.736945;,
  -0.558168;-0.063696;0.827280;,
  0.012798;-0.312968;0.949677;,
  -0.593466;-0.315273;0.740541;,
  -0.582491;-0.347795;-0.734672;,
  -0.939393;-0.322347;0.116762;,
  -0.925078;-0.360476;-0.119528;,
  -0.749453;-0.284342;-0.597887;,
  -0.745520;-0.312813;0.588513;,
  -0.510266;-0.266766;-0.817597;,
  0.539145;-0.266054;-0.799085;,
  -0.533770;-0.298697;0.791120;,
  -0.935160;-0.354226;-0.000425;,
  -0.869624;0.493338;0.019296;,
  -0.625741;0.779667;0.023832;,
  0.999876;-0.013105;-0.008724;,
  -0.744656;-0.384660;0.545458;,
  -0.687562;0.517968;0.508889;,
  -0.479093;0.801782;0.357233;,
  0.803407;0.002104;-0.595427;,
  -0.154655;-0.407885;0.899840;,
  -0.147070;0.495539;0.856044;,
  -0.103809;0.789477;0.604937;,
  0.153398;0.063084;-0.986149;,
  0.485068;-0.412236;0.771214;,
  0.448615;0.493426;0.745168;,
  0.311853;0.794599;0.520923;,
  -0.532876;0.057289;-0.844252;,
  0.870696;-0.404125;0.280306;,
  0.832372;0.488938;0.260952;,
  0.576341;0.796588;0.182422;,
  -0.949809;0.030086;-0.311380;,
  0.863329;-0.407695;-0.297401;,
  0.829353;0.480168;-0.285677;,
  0.579422;0.789924;-0.200726;,
  -0.944189;0.047020;0.326030;,
  0.483556;-0.399369;-0.778896;,
  0.463012;0.496159;-0.734470;,
  0.320618;0.796699;-0.512323;,
  -0.523575;0.021224;0.851715;,
  -0.127723;-0.370197;-0.920131;,
  -0.099325;0.486818;-0.867838;,
  -0.061369;0.780826;-0.621727;,
  0.131663;-0.003613;0.991288;,
  -0.533857;-0.536197;-0.653827;,
  -0.663953;0.529751;-0.527761;,
  -0.452744;0.814605;-0.362548;,
  0.782188;-0.010907;0.622947;,
  -0.825564;0.548797;0.131401;,
  -0.286239;-0.938728;0.191981;,
  0.521702;0.573040;-0.632023;,
  0.199533;-0.754489;-0.625247;,
  0.819402;0.545782;-0.175225;,
  0.692772;-0.720680;0.026225;,
  -0.520236;0.581606;0.625372;,
  -0.196043;-0.767092;0.610850;,
  0.010426;0.999938;-0.003979;,
  0.007051;-0.999965;-0.004495;,
  0.079022;0.000444;-0.996873;,
  0.556876;0.035557;-0.829834;,
  -0.995843;0.044450;0.079505;,
  0.989182;0.046935;-0.138979;,
  -0.684440;0.203422;0.700116;,
  0.965989;0.026156;0.257256;,
  -0.754651;0.500137;0.424694;,
  -0.760671;-0.487981;0.428082;,
  0.459639;0.858322;-0.228068;,
  0.459637;-0.858323;-0.228067;,
  -0.471351;0.841111;0.265255;,
  -0.487264;-0.829085;0.274210;,
  -0.114316;0.991359;0.064332;,
  -0.114329;-0.991357;0.064339;,
  0.858258;0.353309;-0.372243;,
  0.858259;-0.353309;-0.372243;,
  -0.802408;-0.000670;-0.596776;,
  -0.848688;0.000089;-0.528894;,
  -0.566893;-0.001534;-0.823790;,
  -0.871448;-0.007870;0.490425;,
  -0.157652;-0.000787;-0.987494;,
  0.407582;-0.001926;0.913167;,
  0.038731;0.000000;-0.999250;,
  0.620545;-0.000839;0.784170;,
  0.927741;0.000000;-0.373224;,
  0.648717;-0.000416;0.761030;,
  0.678931;0.500142;-0.537503;,
  0.684348;-0.487987;-0.541791;,
  -0.418298;0.858324;0.297165;,
  -0.418296;-0.858325;0.297164;,
  0.424057;0.841112;-0.335716;,
  0.438374;-0.829087;-0.347050;,
  0.102844;0.991360;-0.081419;,
  0.102856;-0.991358;-0.081428;,
  -0.789457;0.353314;0.501924;,
  -0.789457;-0.353314;0.501924;,
  0.885881;-0.000670;0.463911;,
  0.920969;0.000089;0.389636;,
  0.688777;-0.001534;0.724972;,
  0.784009;-0.007870;-0.620700;,
  0.310195;-0.000787;0.950673;,
  -0.545417;-0.001927;-0.838163;,
  0.118093;0.000000;0.993003;,
  -0.735582;-0.000839;-0.677435;,
  -0.857933;0.000000;0.513762;,
  -0.759788;-0.000416;-0.650171;,
  -0.657627;-0.753238;-0.012583;,
  -0.507137;-0.779184;0.368354;,
  -0.100658;-0.804033;0.586002;,
  0.337437;-0.794779;0.504443;,
  0.592882;-0.779975;0.200326;,
  0.580939;-0.788666;-0.201287;,
  0.324341;-0.777631;-0.538604;,
  -0.103406;-0.756024;-0.646324;,
  -0.499439;-0.770198;-0.396681;,
  -0.974690;0.129494;-0.182240;,
  0.088929;0.409240;-0.908083;,
  0.055278;-0.408430;-0.911114;,
  -0.927289;0.019638;-0.373830;,
  -0.888312;-0.297654;-0.349719;,
  -0.981294;-0.172860;0.084745;,
  -0.870965;0.334911;-0.359521;,
  0.865826;-0.012704;-0.500184;,
  -0.865281;-0.011251;0.501161;,
  0.896025;0.376536;0.235287;,
  0.912167;-0.327577;0.246261;,
  -0.064082;-0.432030;0.899580;,
  -0.097916;-0.001701;0.995193;,
  -0.112612;0.428960;0.896277;,
  -0.801492;-0.053796;-0.595580;,
  -0.848682;0.001584;-0.528901;,
  -0.848692;-0.001405;-0.528886;,
  -0.801056;0.052458;-0.596286;,
  -0.563183;0.111782;-0.818736;,
  -0.563298;-0.114865;-0.818230;,
  -0.157636;0.056759;-0.985865;,
  -0.157146;-0.058330;-0.985851;,
  0.288719;-0.002985;0.957409;,
  0.287958;-0.053299;0.956159;,
  0.406547;-0.057154;0.911841;,
  0.407373;0.053308;0.911705;,
  0.288749;0.047336;0.956234;,
  0.038731;0.000000;-0.999250;,
  0.619308;-0.060579;0.782808;,
  0.619566;0.058899;0.782732;,
  0.648497;-0.030202;0.760618;,
  0.648360;0.029370;0.760767;,
  0.580915;0.000000;0.813964;,
  0.884791;-0.053796;0.462873;,
  0.920964;0.001583;0.389645;,
  0.920972;-0.001404;0.389627;,
  0.884470;0.052457;0.463639;,
  0.684322;0.111781;0.720561;,
  0.684357;-0.114863;0.720043;,
  0.309923;0.056758;0.949066;,
  0.309438;-0.058329;0.949129;,
  -0.434933;-0.002985;-0.900458;,
  -0.433985;-0.053306;-0.899342;,
  -0.544187;-0.057159;-0.837015;,
  -0.544981;0.053313;-0.836751;,
  -0.434778;0.047343;-0.899292;,
  -0.734147;-0.060580;-0.676283;,
  -0.734389;0.058901;-0.676168;,
  -0.759506;-0.030203;-0.649798;,
  -0.759395;0.029371;-0.649967;,
  -0.701104;0.000000;-0.713059;,
  -0.701104;0.000000;-0.713059;,
  -0.701104;0.000000;-0.713059;;
  242;
  4;17,3,9,19;,
  4;20,22,10,5;,
  4;25,17,19,27;,
  4;25,27,8,1;,
  4;28,7,11,30;,
  4;28,30,22,20;,
  4;32,27,19,33;,
  4;32,33,21,29;,
  4;32,29,12,34;,
  4;32,34,8,27;,
  4;33,19,9,35;,
  4;33,35,13,21;,
  4;36,15,31,38;,
  4;36,38,30,11;,
  4;37,10,22,39;,
  4;37,39,23,14;,
  4;38,31,23,39;,
  4;38,39,22,30;,
  4;40,24,16,41;,
  4;40,41,17,25;,
  4;40,25,1,42;,
  4;40,42,0,24;,
  4;41,16,2,43;,
  4;41,43,3,17;,
  4;44,7,28,46;,
  4;44,46,26,6;,
  4;45,4,18,47;,
  4;45,47,20,5;,
  4;46,28,20,47;,
  4;46,47,18,26;,
  4;48,49,2,16;,
  4;48,16,24,50;,
  4;50,24,0,51;,
  4;52,53,29,21;,
  4;54,18,4,55;,
  4;54,55,49,48;,
  4;54,48,50,56;,
  4;54,56,26,18;,
  4;55,45,43,49;,
  4;56,50,51,57;,
  4;56,57,6,26;,
  4;45,5,3,43;,
  4;57,51,42,44;,
  4;5,10,9,3;,
  4;44,42,1,7;,
  4;10,37,35,9;,
  4;7,1,8,11;,
  4;37,14,13,35;,
  4;11,8,34,36;,
  4;14,58,52,13;,
  4;36,34,12,15;,
  4;58,23,31,59;,
  4;58,59,53,52;,
  4;15,12,53,59;,
  3;45,55,4;,
  3;43,2,49;,
  3;14,23,58;,
  3;13,52,21;,
  3;42,51,0;,
  3;12,29,53;,
  3;44,6,57;,
  3;15,59,31;,
  4;72,68,62,73;,
  4;72,74,60,68;,
  4;75,64,69,77;,
  4;76,77,69,66;,
  4;78,72,73,79;,
  4;78,80,74,72;,
  4;81,75,77,83;,
  4;82,83,77,76;,
  4;84,126,80,85;,
  4;84,85,127,128;,
  4;84,128,129,86;,
  4;84,86,130,126;,
  4;131,132,133,88;,
  4;131,88,68,60;,
  4;88,133,134,89;,
  4;88,89,135,68;,
  4;136,137,138,91;,
  4;136,91,139,140;,
  4;91,138,141,92;,
  4;91,92,142,139;,
  4;93,78,79,94;,
  4;93,95,80,78;,
  4;143,79,92,96;,
  4;95,97,85,80;,
  4;96,92,141,98;,
  4;97,99,127,85;,
  4;144,81,83,100;,
  4;99,100,83,82;,
  4;101,95,93,102;,
  4;145,146,70,61;,
  4;145,61,87,103;,
  4;101,147,97,95;,
  4;102,93,94,104;,
  4;146,148,63,70;,
  4;103,87,67,105;,
  4;147,105,99,97;,
  4;104,94,96,106;,
  4;148,149,90,63;,
  4;150,67,71,107;,
  4;150,107,100,99;,
  4;106,96,98,108;,
  4;106,108,65,90;,
  4;107,71,65,151;,
  4;107,152,144,100;,
  4;109,109,109,109;,
  4;109,109,109,109;,
  4;109,109,109,109;,
  4;109,109,109,109;,
  4;110,70,63,111;,
  4;110,112,61,70;,
  4;111,63,90,113;,
  4;112,114,87,61;,
  4;113,90,65,115;,
  4;114,116,67,87;,
  4;115,65,71,117;,
  4;116,153,71,67;,
  4;118,110,111,119;,
  4;154,155,155,154;,
  4;154,154,120,120;,
  4;118,156,112,110;,
  4;119,111,113,121;,
  4;155,157,157,155;,
  4;120,120,122,122;,
  4;156,158,114,112;,
  4;121,113,115,123;,
  4;157,159,159,157;,
  4;122,122,124,124;,
  4;158,160,116,114;,
  4;123,115,117,125;,
  4;159,161,161,159;,
  4;124,124,162,162;,
  4;160,163,153,116;,
  4;164,165,169,168;,
  4;165,166,170,169;,
  4;167,167,171,171;,
  4;256,164,168,257;,
  4;168,169,173,172;,
  4;169,170,174,173;,
  4;171,171,175,175;,
  4;257,168,172,258;,
  4;172,173,177,176;,
  4;173,174,178,177;,
  4;175,175,179,179;,
  4;258,172,176,259;,
  4;176,177,181,180;,
  4;177,178,182,181;,
  4;179,179,183,183;,
  4;259,176,180,260;,
  4;180,181,185,184;,
  4;181,182,186,185;,
  4;183,183,187,187;,
  4;260,180,184,261;,
  4;184,185,189,188;,
  4;185,186,190,189;,
  4;187,187,191,191;,
  4;261,184,188,262;,
  4;188,189,193,192;,
  4;189,190,194,193;,
  4;191,191,195,195;,
  4;262,188,192,263;,
  4;192,193,197,196;,
  4;193,194,198,197;,
  4;195,195,199,199;,
  4;263,192,196,264;,
  4;265,197,165,164;,
  4;197,198,166,165;,
  4;199,199,167,167;,
  4;264,196,164,256;,
  4;208,204,202,208;,
  4;208,208,200,206;,
  4;209,207,201,209;,
  4;209,209,203,205;,
  4;210,266,202,211;,
  4;210,211,203,267;,
  4;268,269,270,212;,
  4;268,212,200,271;,
  4;211,202,204,213;,
  4;211,213,272,272;,
  4;212,270,273,214;,
  4;212,214,206,200;,
  4;213,204,274,215;,
  4;213,215,275,205;,
  4;276,207,276,277;,
  4;214,277,278,206;,
  4;220,216,216,220;,
  4;221,221,217,217;,
  4;222,220,220,222;,
  4;222,222,218,218;,
  4;223,219,219,223;,
  4;223,223,221,221;,
  4;224,224,218,218;,
  4;225,225,219,219;,
  4;226,279,280,227;,
  4;226,227,281,282;,
  4;226,282,283,228;,
  4;226,228,284,279;,
  4;229,217,217,229;,
  4;229,229,216,216;,
  4;228,283,285,230;,
  4;228,230,286,284;,
  4;287,288,289,231;,
  4;287,231,290,291;,
  4;230,285,292,232;,
  4;230,232,292,286;,
  4;231,289,293,233;,
  4;231,233,294,290;,
  4;234,224,224,234;,
  4;234,234,225,225;,
  4;233,293,295,235;,
  4;233,235,296,294;,
  4;297,297,296,235;,
  4;297,235,295,297;,
  4;240,236,236,240;,
  4;241,241,237,237;,
  4;242,240,240,242;,
  4;242,242,238,238;,
  4;243,239,239,243;,
  4;243,243,241,241;,
  4;244,244,238,238;,
  4;245,245,239,239;,
  4;246,298,299,247;,
  4;246,247,300,301;,
  4;246,301,302,248;,
  4;246,248,303,298;,
  4;249,237,237,249;,
  4;249,249,236,236;,
  4;248,302,304,250;,
  4;248,250,305,303;,
  4;306,307,308,251;,
  4;306,251,309,310;,
  4;250,304,252,252;,
  4;250,252,252,305;,
  4;251,308,311,253;,
  4;251,253,312,309;,
  4;254,244,244,254;,
  4;254,254,245,245;,
  4;253,311,313,255;,
  4;253,255,314,312;,
  4;315,316,314,255;,
  4;315,255,313,317;;
 }
}
