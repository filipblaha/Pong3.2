﻿#include "Profily.h"

XMLDocument xmlDoc;

//-----------------------  Ulozeni profilu  -----------------------//

void Profily::UlozeniProfilu(int profil)
{
	list<string> nazev_profil = NacteniNazvuProfilu();
	list<vector<char>> ovladani_profil;
	list<vector<int>> data_profil;

	for (int i = 0; i < pocet_profilu; i++)
	{
		if (i == profil)
			data_profil.push_back(VlozeniDatDoVektoru());
		else
			data_profil.push_back(NacteniDatProfilu(i));
	}

	for (int i = 0; i < pocet_profilu; i++)
	{
		if (i == profil)
			ovladani_profil.push_back(VlozeniOvladaniDoVektoru());
		else
			ovladani_profil.push_back(NacteniOvladaniProfilu(i));
	} 

	ZapsaniProfilu(nazev_profil, data_profil, ovladani_profil);
}
vector<int> Profily::VlozeniDatDoVektoru()
{
	vector<int> data_profil;

	data_profil.push_back(jazyk);
	data_profil.push_back(level);
	data_profil.push_back(exp);
	data_profil.push_back(plosina_skin);
	data_profil.push_back(mic_skin);
	data_profil.push_back(highscore_cas);
	data_profil.push_back(highscore_znicenych_bloku);

	return data_profil;
}
vector<char> Profily::VlozeniOvladaniDoVektoru()
{
	vector<char> ovladani_profil;

	ovladani_profil.push_back(pohyb_vlevo);
	ovladani_profil.push_back(pohyb_vpravo);
	ovladani_profil.push_back(pouziti_schopnosti);
	ovladani_profil.push_back(pauza);

	return ovladani_profil;
}

void Profily::VytvoreniNovehoProfilu(string nazev_noveho_profilu)
{
	vector<int> data_noveho_profilu;
	vector<char> ovladani_noveho_profilu;
	list<vector<int>> data_profil;
	list<vector<char>> ovladani_profil;


	list<string> nazev_profil = NacteniNazvuProfilu();

	for (int i = 0; i < 7; i++)
	{
		if (i == 3 || i == 4)
			data_noveho_profilu.push_back(1);
		else
			data_noveho_profilu.push_back(0);
	}
	for (int i = 0; i < pocet_profilu; i++)
	{
		data_profil.push_back(NacteniDatProfilu(i));
	}

	ovladani_noveho_profilu.push_back('A');
	ovladani_noveho_profilu.push_back('D');
	ovladani_noveho_profilu.push_back(char(32));
	ovladani_noveho_profilu.push_back(char(27));
	for (int i = 0; i < pocet_profilu; i++)
	{
		ovladani_profil.push_back(NacteniOvladaniProfilu(i));
	}

	itrs = nazev_profil.begin();
	itrs++;
	nazev_profil.insert(itrs, nazev_noveho_profilu);

	itri = data_profil.begin();
	itri++;
	data_profil.insert(itri, data_noveho_profilu);

	itrc = ovladani_profil.begin();
	itrc++;
	ovladani_profil.insert(itrc, ovladani_noveho_profilu);

	pocet_profilu++;

	ZapsaniProfilu(nazev_profil, data_profil, ovladani_profil);
}
void Profily::OdstraneniProfilu(int profil)
{
	list<string> nazev_profil;
	list<vector<char>> ovladani_profil;
	list<vector<int>> data_profil;	


	nazev_profil = NacteniNazvuProfilu();

	for (int i = 0; i < pocet_profilu; i++)
	{
		data_profil.push_back(NacteniDatProfilu(i));
	}

	for (int i = 0; i < pocet_profilu; i++)
	{
		ovladani_profil.push_back(NacteniOvladaniProfilu(i));
	}

	itrs = nazev_profil.begin();
	advance(itrs, profil);
	nazev_profil.erase(itrs);

	itrc = ovladani_profil.begin();
	advance(itrc, profil);
	ovladani_profil.erase(itrc);

	itri = data_profil.begin();
	advance(itri, profil);
	data_profil.erase(itri);


	pocet_profilu--;

	ZapsaniProfilu(nazev_profil, data_profil, ovladani_profil);
}

void Profily::ZapsaniProfilu(list<string> nazev, list<vector<int>> data, list<vector<char>> ovladani)
{
	ZapsaniNazvuProfilu(nazev);
	ZapsaniDatAOvladaniProfilu(data, ovladani);
}
void Profily::ZapsaniNazvuProfilu(list<string> nazev)
{
	xmlDoc.LoadFile("Profily.xml");

	XMLNode* root = xmlDoc.FirstChild();
	XMLElement* base = root->FirstChildElement("Zakladni");
	XMLElement* profily_nazev = base->FirstChildElement("Nazev_profilu");

	profily_nazev->Parent()->DeleteChildren();

	for (itrs = nazev.begin(); itrs != nazev.end(); itrs++)
	{
		profily_nazev = xmlDoc.NewElement("Nazev_profilu");
		string temp = *itrs;
		for (int i = 0; i < temp.size(); i++)
		{
			XMLElement* pismeno = xmlDoc.NewElement("Pismeno");
			pismeno->SetText(temp.at(i));
			profily_nazev->InsertEndChild(pismeno);
		}
		base->InsertEndChild(profily_nazev);
	}
	xmlDoc.SaveFile("Profily.xml");
}
void Profily::ZapsaniDatAOvladaniProfilu(list<vector<int>> data, list<vector<char>> ovladani)
{
	xmlDoc.LoadFile("Profily.xml");

	XMLNode* root = xmlDoc.FirstChild();
	XMLElement* profily = root->FirstChildElement("Profily");
	XMLElement* prof = profily->FirstChildElement("Profil");
	prof->Parent()->DeleteChildren();


	vector<int> tempi;
	vector<char> tempc;

	itri = data.begin();
	itrc = ovladani.begin();
	for (int j = 0; j < pocet_profilu; j++, itri++, itrc++)
	{
		prof = xmlDoc.NewElement("Profil");
		XMLElement* profily_data = xmlDoc.NewElement("Data");
		tempi = *itri;
		for (int i = 0; i < tempi.size(); i++)
		{
			XMLElement* hodnoty = xmlDoc.NewElement("Hodnota");
			hodnoty->SetText(tempi.at(i));
			profily_data->InsertEndChild(hodnoty);
		}
		prof->InsertEndChild(profily_data);

		XMLElement* profily_ovladani = xmlDoc.NewElement("Ovladani");
		tempc = *itrc;
		for (int i = 0; i < tempc.size(); i++)
		{
			XMLElement* hodnoty = xmlDoc.NewElement("Hodnota");
			hodnoty->SetText(tempc.at(i));
			profily_ovladani->InsertEndChild(hodnoty);
		}
		prof->InsertEndChild(profily_ovladani);
		profily->InsertEndChild(prof);
	}
	xmlDoc.SaveFile("Profily.xml");
}

//-----------------------  Nacteni vsech profilu  -----------------------//

list<string> Profily::NacteniNazvuProfilu()
{
	int data = 0;
	string vektor_pismen;
	list<string> v_v_pismen;

	xmlDoc.LoadFile("Profily.xml");

	NacteniPoctuProfilu();

	XMLNode* root = xmlDoc.FirstChild();
	XMLElement* base = root->FirstChildElement("Zakladni");
	XMLElement* profily_nazev = base->FirstChildElement("Nazev_profilu");
	while (profily_nazev != nullptr)
	{
		XMLElement* hodnoty = profily_nazev->FirstChildElement("Pismeno");
		while (hodnoty != nullptr)
		{
			hodnoty->QueryIntText(&data);
			vektor_pismen.push_back(data);
			hodnoty = hodnoty->NextSiblingElement("Pismeno");
		}
		v_v_pismen.push_back(vektor_pismen);
		vektor_pismen.clear();
		profily_nazev = profily_nazev->NextSiblingElement("Nazev_profilu");
	}
	return v_v_pismen;
}
vector<vector<int>> Profily::NacteniDat()
{
	int data = 0;
	vector<int> vektor_dat;
	vector<vector<int>> v_v_dat;

	xmlDoc.LoadFile("Profily.xml");

	XMLNode* root = xmlDoc.FirstChild();
	XMLElement* profily = root->FirstChildElement("Profily");
	XMLElement* prof = profily->FirstChildElement("Profil");
	while (prof != nullptr)
	{
		XMLElement* profily_data = prof->FirstChildElement("Data");
		XMLElement* hodnoty = profily_data->FirstChildElement("Hodnota");
		while (hodnoty != nullptr)
		{
			hodnoty->QueryIntText(&data);
			vektor_dat.push_back(data);
			hodnoty = hodnoty->NextSiblingElement("Hodnota");
		}
		v_v_dat.push_back(vektor_dat);
		vektor_dat.clear();
		prof = prof->NextSiblingElement("Profil");
	}
	return v_v_dat;
}
vector<vector<char>> Profily::NacteniOvladani()
{
	int data;
	vector<char> vektor_ovladani;
	vector<vector<char>> v_v_ovladani;

	xmlDoc.LoadFile("Profily.xml");

	XMLNode* root = xmlDoc.FirstChild();
	XMLElement* profily = root->FirstChildElement("Profily");
	XMLElement* prof = profily->FirstChildElement("Profil");
	while (prof != nullptr)
	{
		XMLElement* profily_ovladani = prof->FirstChildElement("Ovladani");
		XMLElement* hodnoty = profily_ovladani->FirstChildElement("Hodnota");
		while (hodnoty != nullptr)
		{
			hodnoty->QueryIntText(&data);
			vektor_ovladani.push_back(data);
			hodnoty = hodnoty->NextSiblingElement("Hodnota");
		}
		v_v_ovladani.push_back(vektor_ovladani);
		vektor_ovladani.clear();
		prof = prof->NextSiblingElement("Profil");
	}
	return v_v_ovladani;
}

int Profily::NacteniPoctuProfilu()
{
	vector<vector<int>> v_v_dat = NacteniDat();
	return v_v_dat.size();
}
list<int> Profily::NacteniUrovniProfilu()
{
	vector<vector<int>> v_v_dat = NacteniDat();
	list<int> list_dat;

	for (int i = 0; i < v_v_dat.size(); i++)
	{
		list_dat.push_back(v_v_dat.at(i).at(1));
	}
	return list_dat;
}

//-----  Nacteni vybreneho profilu  -----//
vector<int> Profily::NacteniDatProfilu(int profil)
{
	vector<vector<int>> v_v_dat = NacteniDat();
	return v_v_dat.at(profil);
}
vector<char> Profily::NacteniOvladaniProfilu(int profil)
{
	vector<vector<char>> v_v_ovladani = NacteniOvladani();
	return v_v_ovladani.at(profil);
}

void Profily::VybraniProfilu(int profil)
{
	vector<int> vektor_dat = NacteniDatProfilu(profil);
	vector<char> vektor_ovladani = NacteniOvladaniProfilu(profil);

	jsem_v_profilu = profil;

	jazyk = vektor_dat.at(0);
	level = vektor_dat.at(1);
	exp = vektor_dat.at(2);
	plosina_skin = vektor_dat.at(3);
	mic_skin = vektor_dat.at(4);
	highscore_cas = vektor_dat.at(5);
	highscore_znicenych_bloku = vektor_dat.at(6);

	pohyb_vlevo = vektor_ovladani.at(0);
	pohyb_vpravo = vektor_ovladani.at(1);
	pouziti_schopnosti = vektor_ovladani.at(2);
	pauza = vektor_ovladani.at(3);
}

//-----------------------  Nacteni skinu  -----------------------//

vector<wstring> Profily::NacteniSkiny()
{
	vector<wstring> skiny;

	wstring s0 = L"??????";
	wstring s1 = L"IIIIII";
	wstring s2 = L"╒════╕";
	wstring s3 = L"FELZCU";
	wstring s4 = L"◄■■■■►";
	wstring s5;
	for (int i = 0; i < 3; i++)
		s5.push_back(wchar_t(171));
	for (int i = 0; i < 3; i++)
		s5.push_back(wchar_t(187));
	wstring s6 = L"______";

	return skiny = { s0, s1, s2, s3, s4, s5, s6} ;
}
//vector<wchar_t> Profily::NacteniSkinyMic()
//{
//	vector<wchar_t> skiny;
//
//	wchar_t s0 = '?';
//	wchar_t s1 = '0';
//	wchar_t s2 = 'a';
//	wchar_t s3 = 'b';
//	wchar_t s4 = 'c';
//	wchar_t s5 = 'd';
//	wchar_t s6 = 'e';
//
//	return skiny = { s0, s1, s2, s3, s4, s5, s6 };
//}

//-----------------------  Zmena jmena  -----------------------//

void Profily::ZmenaNazvu(string jmeno, int profil)
{
	list<string> nazev_profil = NacteniNazvuProfilu();
	list<vector<char>> ovladani_profil;
	list<vector<int>> data_profil;
	itrs = nazev_profil.begin();

	advance(itrs, profil);
	*itrs = jmeno;

	for (int i = 0; i < pocet_profilu; i++)
	{
		data_profil.push_back(NacteniDatProfilu(i));
	}

	for (int i = 0; i < pocet_profilu; i++)
	{
		ovladani_profil.push_back(NacteniOvladaniProfilu(i));
	}

	ZapsaniProfilu(nazev_profil, data_profil, ovladani_profil);
}