
#include "Source.h"

map<string, string> new_name;

bool ChungMinh(Menhde menhdeCuoi, vector<Luat> MangLuat, vector<Sukien> MangSukien)
{
	BienDung bien_dung;

	vector<Menhde> stack;
	stack.push_back(menhdeCuoi);

	while (!stack.empty())
	{
		Menhde* menhde = &stack.back();

		//cout << "\n\n =========================================================\n";
		//for (size_t i = 0; i < stack.size(); i++)
		//{
		//	cout << "Menhde : ";
		//	for (size_t j = 0; j < stack[i].sukien.size(); j++)
		//	{
		//		cout << stack[i].sukien[j].name << " (";
		//		for (size_t k = 0; k < stack[i].sukien[j].bien.size(); k++)
		//		{
		//			cout << stack[i].sukien[j].bien[k];
		//			if (k!= stack[i].sukien[j].bien.size()-1)
		//			{
		//				cout<<" , ";
		//			}
		//		}
		//		cout << ") \t";
		//	}
		//	cout << "\n";
		//}
		//cout << "=========================================================\n\n";


		int k = Sosanh_MangSukien(menhde, MangSukien);

		if (k == 1) {

			if (bien_dung.bien_dung.size() == 0)
				bien_dung.bien_dung = menhde->bien_dung.bien_dung;
			else
				bien_dung.Giao(menhde->bien_dung);

			stack.pop_back();

			continue;
		}
		else if (k == -1)
		{
			return false;
		}

		vector<Menhde> menhde_new = Sosanh_MangLuat(menhde, MangLuat);

		stack.pop_back();


		if (menhde_new.size() != 0) {
			stack.insert(end(stack), begin(menhde_new), end(menhde_new));
		}
		else
		{
			return false;
		}


	}

	if (bien_dung.bien_dung.size() > 0)
	{
		if (bien_dung.bien_dung[0].size() == 1)
			return false;
	}

	//cout << "\t =======  ======\n";

	//for (size_t i = 0; i < bien_dung.bien_dung.size(); i++)
	//{
	//	for (size_t j = 0; j < bien_dung.bien_dung[i].size(); j++)
	//	{
	//		cout << "\t" << bien_dung.bien_dung[i][j];
	//	}
	//	cout << " \n";
	//}


	for (map<string, string>::iterator it = new_name.begin(); it != new_name.end(); ++it)
	{
		cout << "\t =================\n";

		int pos = bien_dung.ViTriTen(it->first);
		if (pos != -1)
		{
			for (size_t i = 1; i < bien_dung.bien_dung[pos].size(); i++)
			{
				cout << "\t" << it->first << " = " << bien_dung.bien_dung[pos][i] << "\n";
			}
		}

	}


	return true;
}

int Sosanh_bien(string bien, string bien2) {
	if (bien[0] >= 65 && bien[0] <= 90 && bien2[0] >= 65 && bien2[0] <= 90)
	{
		return -2;
	}
	if (bien[0] >= 65 && bien[0] <= 90)
	{
		return -1;
	}
	if (bien2[0] >= 65 && bien2[0] <= 90)
	{
		return 1;
	}
	if (bien == bien2)
	{
		return 1;
	}
	return 0;
}

int Sosanh(Sukien sukien, Sukien sukien2, BienDung* bien_dung) {

	if (sukien.name != sukien2.name) {
		return 0;
	}
	map<string, string>gia_tri;
	for (int i = 0; i < sukien.bien.size(); i++)
	{
		switch (Sosanh_bien(sukien.bien[i], sukien2.bien[i]))
		{
		case 0:
			return 0;
		case 1:
			continue;
		case -1:
			gia_tri[sukien.bien[i]] = sukien2.bien[i];
			break;
		case -2:
			if (sukien.bien[i] == sukien2.bien[i])
				continue;
			new_name[sukien.bien[i]] = sukien2.bien[i];
		}

	}
	if (gia_tri.size() != 0 && bien_dung != NULL) {
		for (map< string, string>::iterator it = gia_tri.begin(); it != gia_tri.end(); ++it)
		{

			bien_dung->ThemBien(it->first, it->second);
		}
	}

	if (sukien.IsNot == sukien2.IsNot) {
		return 1;
	}
	else
	{
		return -1;
	}
}

void Thay_the_bien(map<string, string> bien_thay_the, vector<Menhde>& menhde) {
	for (int i = 0; i < menhde.size(); i++)
	{
		for (int j = 0; j < menhde[i].sukien.size(); j++)
		{
			for (int k = 0; k < menhde[i].sukien[j].bien.size(); k++)
			{
				if (bien_thay_the[menhde[i].sukien[j].bien[k]] != "") {
					menhde[i].sukien[j].bien[k] = bien_thay_the[menhde[i].sukien[j].bien[k]];

				}
			}
		}
	}
}

void Thay_the_bien(map<string, string> bien_thay_the, Sukien& sukien)
{
	for (int i = 0; i < sukien.bien.size(); i++)
		if (bien_thay_the.find(sukien.bien[i]) != bien_thay_the.end())
			sukien.bien[i] = bien_thay_the[sukien.bien[i]];
}

vector<Menhde> Sosanh_MangLuat(Menhde* menhde, vector<Luat> MangLuat) {

	for (int i = 0; i < menhde->sukien.size(); i++)
	{
		Sukien sukien = menhde->sukien[i];

		for (int j = 0; j < MangLuat.size(); j++)
		{
			if (Sosanh(sukien, MangLuat[j].sukienKQ) != 0)
			{
				MenhdeTho menhdetho;
				menhdetho.toantu = OR;

				vector<Menhde> menhde2_list = MangLuat[j].menhdeGoc;

				map<string, string> bien_thay_the;
				for (int k = 0; k < sukien.bien.size(); k++)
				{
					switch (Sosanh_bien(sukien.bien[k], MangLuat[j].sukienKQ.bien[k]))
					{
					case 1:
					case -2:
						bien_thay_the[MangLuat[j].sukienKQ.bien[k]] = sukien.bien[k];
						continue;
					}

				}

				Thay_the_bien(bien_thay_the, menhde2_list);

				MenhdeTho menhde2;
				menhde2.toantu = AND;

				for (int i = 0; i < menhde2_list.size(); i++)
				{
					MenhdeTho temp;
					temp.toantu = OR;
					temp.menhde.push_back(menhde2_list[i]);
					menhde2.menhdetho.push_back(temp);
				}
				menhdetho.menhdetho.push_back(menhde2);

				menhde->sukien.erase(menhde->sukien.begin() + i);
				if (menhde->sukien.size() != 0) {
					MenhdeTho menhde1;
					menhde1.toantu = OR;
					menhde1.menhde.push_back(*menhde);
					menhdetho.menhdetho.push_back(menhde1);
				}


				vector<Menhde> menhde_new = CNF(menhdetho);
				for (int i = 0; i < menhde_new.size(); i++)
				{
					menhde_new[i].bien_dung = menhde->bien_dung;
				}

				return menhde_new;
			}
		}
	}

	return vector<Menhde>();
}

int Sosanh_MangSukien(Menhde* menhde, vector<Sukien> MangSukien) {
	bool IsTrue = false;
	for (int i = 0; i < menhde->sukien.size(); i++)
	{
		Sukien sukien = menhde->sukien[i];

		for (int j = 0; j < MangSukien.size(); j++)
		{
			int k = Sosanh(sukien, MangSukien[j], &menhde->bien_dung);
			if (k == 1)	// menh de dung
			{
				IsTrue = true;
				continue;
			}
			if (k == -1)	// su kien sai
			{
				menhde->sukien.erase(menhde->sukien.begin() + i);
				i--;
			}
		}
	}

	if (IsTrue) {
		return 1;
	}

	if (menhde->sukien.size() == 0)		// menh de sai
	{
		return -1;
	}

	return 0;
}


//=========CNF================

vector<Menhde> CNF(MenhdeTho menhdeTho, bool first) {

	if (menhdeTho.menhde.size() == 1) {

		if (menhdeTho.toantu == ANDNOT || menhdeTho.toantu == ORNOT)
		{
			for (int i = 0; i < menhdeTho.menhde[0].sukien.size(); i++)
			{
				menhdeTho.menhde[0].sukien[i].IsNot = !menhdeTho.menhde[0].sukien[i].IsNot;
			}
		}

		switch (menhdeTho.toantu)
		{
		case OR:
		case ANDNOT:
			return menhdeTho.menhde;
		case AND:
		case ORNOT:
		{
			vector<Menhde> menhde;
			for (int i = 0; i < menhdeTho.menhde[0].sukien.size(); i++)
			{
				Menhde menhde_new;
				menhde_new.sukien.push_back(menhdeTho.menhde[0].sukien[i]);

				menhde.push_back(menhde_new);
			}
			return menhde;
		}
		default:
			cout << "CNF : default\n";
			return vector<Menhde>();
		}
	}

	if (menhdeTho.toantu == ANDNOT || menhdeTho.toantu == ORNOT) {
		menhdeTho.toantu = (-2) / menhdeTho.toantu;
		for (int i = 0; i < menhdeTho.menhdetho.size(); i++)
		{
			menhdeTho.menhdetho[i].toantu = -menhdeTho.menhdetho[i].toantu;
		}
	}

	if (menhdeTho.toantu == AND) {
		vector<Menhde> menhde;
		for (int i = 0; i < menhdeTho.menhdetho.size(); i++)
		{
			vector<Menhde> menhde_con = CNF(menhdeTho.menhdetho[i], false);
			menhde.insert(end(menhde), begin(menhde_con), end(menhde_con));
		}
		return menhde;
	}

	if (menhdeTho.toantu == OR) {
		vector<vector<Menhde>> menhde_OR;
		for (int i = 0; i < menhdeTho.menhdetho.size(); i++)
		{
			vector<Menhde> menhde_con = CNF(menhdeTho.menhdetho[i], false);
			menhde_OR.push_back(menhde_con);
		}

		return OR_to_AND(menhde_OR);
	}

	cout << "CNF : toantu\n";
	return vector<Menhde>();
}

vector<Menhde> OR_to_AND(vector<vector<Menhde>> menhde_OR, int k, Menhde menhde_moi) {
	static vector<Menhde> result;

	if (k >= menhde_OR.size())
	{

		result.push_back(menhde_moi);
		return vector<Menhde>();
	}

	for (size_t i = 0; i < menhde_OR[k].size(); i++)
	{
		vector<Sukien> copy_sukien = menhde_moi.sukien;
		for (int j = 0; j < menhde_OR[k][i].sukien.size(); j++)
		{
			Sukien sukienmoi = menhde_OR[k][i].sukien[j];
			if (!CoTrong_MangSukien(sukienmoi, menhde_moi.sukien))
			{
				menhde_moi.sukien.push_back(sukienmoi);
			}
		}
		OR_to_AND(menhde_OR, k + 1, menhde_moi);
		menhde_moi.sukien = copy_sukien;

	}

	if (k == 0) {
		vector<Menhde> copy = result;
		result.clear();
		return copy;
	}
	return vector<Menhde>();

}

bool CoTrong_MangSukien(Sukien sukien, vector<Sukien> mangSukien) {
	for (int i = 0; i < mangSukien.size(); i++)
	{
		if (sukien.name == mangSukien[i].name)
		{
			bool issame = true;
			for (int j = 0; j < sukien.bien.size(); j++)
			{
				if (sukien.bien[j] != mangSukien[i].bien[j])
				{
					issame = false;
					break;
				}
			}
			if (issame)
			{
				return true;
			}
		}
	}
	return false;

}

//==== Read File =========

Menhde ReadConsole() {

	string line;
	cin >> line;

	int pos = line.find('.');
	if (pos != string::npos)
		line = line.substr(0, pos);

	Sukien sukien = DocSukien(line);
	Menhde menhde;
	menhde.sukien.push_back(sukien);
	return menhde;
}

void ReadLine(string line, vector<Luat>& mangLuat, vector<Sukien>& mangSukien) {

	line.erase(line.end() - 1);

	int pos = line.find(':');
	if (pos != string::npos) {
		Luat luat;
		luat.sukienKQ = DocSukien(line.substr(0, pos));
		DocLuat(line.substr(pos + 2), luat);
		RandomName(luat);
		mangLuat.push_back(luat);
	}
	else
	{
		Sukien sukien = DocSukien(line);
		mangSukien.push_back(sukien);
	}
}

void ReadFile(char* filename, vector<Luat>& mangLuat, vector<Sukien>& mangSukien) {
	fstream f;
	f.open(filename);
	string line;
	getline(f, line);
	while (!f.eof()) {

		if (line.find('/') != string::npos || line.size() == 0) {
			getline(f, line);
			continue;
		}

		ReadLine(line, mangLuat, mangSukien);

		getline(f, line);
	}
	f.close();
}

Sukien DocSukien(string s) {
	Sukien sukien;
	int pre_pos, pos = s.find('(');
	pre_pos = pos + 1;
	sukien.name = s.substr(0, pos);

	while ((pos = s.find(',', pre_pos)) != string::npos)
	{
		string bien = s.substr(pre_pos, pos - pre_pos);
		sukien.bien.push_back(bien);
		pre_pos = pos + 1;
	}

	sukien.bien.push_back(s.substr(pre_pos, s.size() - pre_pos - 1));

	return sukien;
}

MenhdeTho DocMenhdetho(string s, char c, bool first) {
	MenhdeTho menhdetho;

	// ? IsNeg
	bool IsNeg = false;
	if (!first) {

		if (s[s.size() - 1] == ')' && s[s.size() - 2] == ')') {
			if (s[0] == 'n') {
				IsNeg = true;
				s.erase(0, 4);
			}
			if (s[0] == '(') {
				s.erase(0, 1);
				s.erase(s.size() - 1, 1);
			}
		}
	}

	// ? la menh de
	if (s.find("))") == string::npos) {
		bool cochamphay = s.find(';') != string::npos;
		bool cophay = s.find(',') != string::npos;
		if (!cochamphay || !cophay) {	// menh de?

			vector<string> s_sukien;

			if (cochamphay) {
				menhdetho.toantu = OR;
				s_sukien = tim_menhdecon_voikytu(s, ';', false);
			}
			else {
				menhdetho.toantu = AND;
				s_sukien = tim_menhdecon_voikytu(s, ',', false);
			}

			if (IsNeg)
				menhdetho.toantu = -menhdetho.toantu;

			Menhde menhde;
			for (int i = 0; i < s_sukien.size(); i++)
			{
				menhde.sukien.push_back(DocSukien(s_sukien[i]));
			}
			menhdetho.menhde.push_back(menhde);

			return menhdetho;
		}
	}

	char next_c;
	if (c == ';') {
		next_c = ',';
	}
	else
	{
		next_c = ';';
	}


	vector<string> result;
	result = tim_menhdecon_voikytu(s, c);

	if (result.size() != 0) {

		if (c == ';')
			menhdetho.toantu = OR;
		else
			menhdetho.toantu = AND;

		if (IsNeg)
			menhdetho.toantu = -menhdetho.toantu;

		for (int i = 0; i < result.size(); i++)
		{
			menhdetho.menhdetho.push_back(DocMenhdetho(result[i], next_c, false));
		}
		return menhdetho;

	}
	else
	{
		return DocMenhdetho(s, next_c, false);
	}
}

void RandomName(Luat& luat) {
	map<string, string> bien_map;

	for (size_t i = 0; i < luat.menhdeGoc.size(); i++)
	{
		for (size_t j = 0; j < luat.menhdeGoc[i].sukien.size(); j++)
		{
			for (size_t k = 0; k < luat.menhdeGoc[i].sukien[j].bien.size(); k++)
			{
				string bien = luat.menhdeGoc[i].sukien[j].bien[k];

				if (bien[0] >= 65 && bien[0] <= 90)
				{
					bien_map[bien] = bien;
				}
			}
		}
	}

	for (auto& bien : bien_map)
	{
		//srand(time(NULL));
		int ran_num = rand() % 10000;
		bien.second += to_string(ran_num);
		//std::cout << "\n==" << bien.second << "===\n";
	}

	Thay_the_bien(bien_map, luat.menhdeGoc);
	Thay_the_bien(bien_map, luat.sukienKQ);
}

void DocLuat(string s, Luat& luat) {
	MenhdeTho menhdetho = DocMenhdetho(s, ';');
	vector<Menhde> menhde = CNF(menhdetho);
	luat.menhdeGoc.insert(end(luat.menhdeGoc), begin(menhde), end(menhde));
}

vector<string> tim_menhdecon_voikytu(string s, char c, bool coNgoac) {
	vector<string> result;
	int pre_pos = 0, temp_pos = 0, pos;
	while ((pos = s.find(c, temp_pos)) != string::npos)
	{
		int count_moNgoac = count(s.begin() + pre_pos, s.begin() + pos, '(');
		int count_dongNgoac = count(s.begin() + pre_pos, s.begin() + pos, ')');

		if (count_moNgoac == count_dongNgoac) {
			result.push_back(s.substr(pre_pos, pos - pre_pos));
			pre_pos = pos + 1;
		}

		temp_pos = pos + 1;

	}
	result.push_back(s.substr(pre_pos, s.size() - pre_pos));

	return result;
}
//=========Print================
void PrintMang(vector<Luat>& mangLuat, vector<Sukien>& mangSukien) {

	for (int i = 0; i < mangSukien.size(); i++)
	{
		cout << "\t" << mangSukien[i].name << " : ";
		for (int j = 0; j < mangSukien[i].bien.size(); j++)
		{
			cout << mangSukien[i].bien[j] << "   ";
		}
		cout << "\n";
	}

	cout << "=====In Luat=====\n";
	for (int i = 0; i < mangLuat.size(); i++)
	{
		Luat luat = mangLuat[i];

		cout << "\t" << luat.sukienKQ.name << " : ";
		for (int i = 0; i < luat.menhdeGoc.size(); i++)
		{
			cout << " ( ";
			for (int j = 0; j < luat.menhdeGoc[i].sukien.size(); j++)
			{
				cout << luat.menhdeGoc[i].sukien[j].name << ":";
				for (int k = 0; k < luat.menhdeGoc[i].sukien[j].bien.size(); k++)
				{
					cout << luat.menhdeGoc[i].sukien[j].bien[k] << ",";
				}
				cout << "  ";
			}
			cout << ") ";
		}
		cout << "\n";

	}
}


int main() {

	vector<Luat> mangLuat;
	vector<Sukien> mangSukien;

	// FitHcmusDatabase.pl
	// BritishRoyalFamily.pl
	ReadFile((char*)"BritishRoyalFamily.pl", mangLuat, mangSukien);

	//PrintMang(mangLuat, mangSukien);
	while (true)
	{
		Menhde menhde = ReadConsole();
		if (ChungMinh(menhde, mangLuat, mangSukien)) 
			cout << "Chung minh = True !";
		else
			cout << "Chung minh = False !";
		cout << "\n==========================================================\n\n";
	}

	return 0;
}

void BienDung::ThemBien(string ten, string bien) {

	int pos = ViTriTen(ten);
	if (pos == -1)
	{
		vector<string> bienmoi;
		bienmoi.push_back(ten);
		bienmoi.push_back(bien);
		bien_dung.push_back(bienmoi);
	}
	else
	{
		bien_dung[pos].push_back(bien);
	}

}

void BienDung::Giao(BienDung biendung2) {
	map<int, int> hang_giao;	// bang nay
	vector<int> hang_khac;	// bang kia
	int sohang = bien_dung.size();

	for (size_t i = 0; i < bien_dung.size(); i++)
	{
		int pos = biendung2.ViTriTen(bien_dung[i][0]);
		if (pos != -1)
			hang_giao[i] = pos;
	}
	for (size_t i = 0; i < biendung2.bien_dung.size(); i++)
		if (ViTriTen(biendung2.bien_dung[i][0]) == -1)
			hang_khac.push_back(i);

	for (size_t i = 1; i < bien_dung[0].size(); i++)
	{
		bool haveRow = false;

		for (size_t j = 1; j < biendung2.bien_dung[0].size(); j++)
		{
			bool match = true;
			for (auto hang : hang_giao)
				if (bien_dung[hang.first][i] != biendung2.bien_dung[hang.second][j])
					match = false;

			if (match) {
				haveRow = true;
				for (auto hang : hang_khac)
					ThemBien(biendung2.bien_dung[hang][0], biendung2.bien_dung[hang][j]);
				//for (size_t k = 1; k < bien_dung.size(); k++) {
				//	if (hang_giao.find(k) == hang_giao.end())
				//	{
				//		ThemBien(bien_dung[k][0], bien_dung[k][i]);
				//	}
				//}

			}
		}

		if (haveRow)
		{

		}
		else
		{

			for (size_t j = 0; j < sohang; j++)
			{
				bien_dung[j].erase(bien_dung[j].begin() + i);
			}
			i--;
		}
	}
}

int BienDung::ViTriTen(string ten) {
	for (size_t i = 0; i < bien_dung.size(); i++)
	{
		if (bien_dung[i][0] == ten)
		{
			return i;
		}
	}
	return -1;
}
