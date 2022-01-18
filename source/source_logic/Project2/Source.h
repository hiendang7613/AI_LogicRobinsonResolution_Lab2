#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Sukien
{
	string name;
	bool IsNot = true;
	vector<string>bien;
};


class BienDung
{
public:
	BienDung() {}
	~BienDung() {}
	//	Z	i	k	l
	//	X	a	b	c
	//	Y	m	n	p 
	//

	void ThemBien(string ten, string bien);
	void Giao(BienDung biendung2);

	int ViTriTen(string ten);

	vector<vector<string>> bien_dung;
};

struct Menhde
{
	vector<Sukien> sukien;
	BienDung bien_dung;
};

struct Luat
{
	Sukien sukienKQ;
	vector<Menhde> menhdeGoc;
};


enum Toantu
{
	ORNOT = -1,
	OR = 1,
	ANDNOT = -2,
	AND = 2
};

struct MenhdeTho
{
	int toantu;
	vector<MenhdeTho> menhdetho;
	vector<Menhde> menhde;
};

bool ChungMinh(Menhde menhdeCuoi, vector<Luat> MangLuat, vector<Sukien> MangSukien);

int Sosanh_bien(string bien, string bien2);

int Sosanh(Sukien sukien, Sukien sukien2, BienDung* = NULL);

void Thay_the_bien(map<string, string> bien_thay_the, vector<Menhde>& menhde);

void Thay_the_bien(map<string, string> bien_thay_the, Sukien& sukien);

vector<Menhde> Sosanh_MangLuat(Menhde* menhde, vector<Luat> MangLuat);

int Sosanh_MangSukien(Menhde* menhde, vector<Sukien> MangSukien);

vector<Menhde> CNF(MenhdeTho menhdeTho, bool first = true);

vector<Menhde> OR_to_AND(vector<vector<Menhde>> menhde_OR, int k = 0, Menhde menhde_moi = Menhde());

bool CoTrong_MangSukien(Sukien sukien, vector<Sukien> mangSukien);

void ReadLine(string line, vector<Luat>& mangLuat, vector<Sukien>& mangSukien);

void ReadFile(char* filename, vector<Luat>& mangLuat, vector<Sukien>& mangSukien);

Sukien DocSukien(string s);

MenhdeTho DocMenhdetho(string s, char c, bool first = true);

void RandomName(Luat& luat);

void DocLuat(string s, Luat& luat);

vector<string> tim_menhdecon_voikytu(string s, char c, bool coNgoac = true);

void PrintMang(vector<Luat>& mangLuat, vector<Sukien>& mangSukien);
