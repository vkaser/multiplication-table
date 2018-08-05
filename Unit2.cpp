//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <jpeg.hpp>
#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
// настройка размера изображения
Image1->Proportional = true;
Image1->Height = 480;
Image1->Width = 480;
Image1->Left = 32;
Image1->Top = 32;
randomize();
//  загрузка изображения
int p = random(44)+1;
Image1->Picture->LoadFromFile("\Image\\" + IntToStr(p)+".jpg");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
Form1->Show();
Form2->Release();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::N1Click(TObject *Sender)
{
Form1->Show();
Form2->Release();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::N2Click(TObject *Sender)
{
Application->MessageBoxA("Гребенников Сергей\n\nТаблица умножения\
\n\n\t2011","Справка",MB_ICONQUESTION);
}
//---------------------------------------------------------------------------

