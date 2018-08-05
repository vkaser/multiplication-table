//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <DateUtils.hpp>
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
Graphics::TBitmap *bgp1;

AnsiString sMonth[] = {"","января","февраля","марта",
						"апреля","мая","июня","июля",
						"августа","сентября","октября",
						"ноября","декабря"};

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   bgp1 = new Graphics::TBitmap();
   try
   {
	  bgp1->LoadFromFile("187.bmp");
   }
   catch (EFOpenError &e)
   {  }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
int h;  			// текущее время
AnsiString mes; 	// сообщение
int wt, ht;  		// размер (ширина и высота)
					// области вывода текста
int x,y;            // координаты области вывода текста

h = HourOf( Now () );

if ( h <= 4 ) mes = "Доброй ночи!";
else if ( h < 12 ) mes = "Доброе утро!";
else if ( h <= 16 ) mes = "Добрый день!";
else mes = "Добрый вечер!";

Form1->Canvas->Font->Size = 25;

// определить размер области вывода текста
wt = Canvas->TextWidth(mes);
ht = Canvas->TextHeight(mes);

x = (ClientWidth - wt)/2;
y = 4;

// фоновая картинка
Canvas->Draw(0,0,bgp1);

//  для того чтобы область вывода текста
//  была прозрачной

Canvas->Brush->Style = bsClear;
Canvas->TextOutA(x,y,mes);

y = y + ht;  // координата нижней границы
			 // области вывода текста

//  дата и день недели

mes = FormatDateTime("Сегодня d", Now());
mes = mes + " " + sMonth[ MonthOf( Now() )] + ", " +
		FormatDateTime("dddd",Now());

//  размер шрифта на 4 пункта
//  меньше шрифта приветствия
Canvas->Font->Size -= 4;

wt = Canvas->TextWidth(mes);
ht = Canvas->TextHeight(mes);

x = (ClientWidth - wt)/2;
y = y + 25;

Canvas->TextOutA(x,y,mes);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
if ( ComboBox1->ItemIndex == -1) {
	Application->MessageBox("Выберите уровень",
	"",MB_ICONWARNING);
	ComboBox1->SetFocus();
	return;
}
Application->CreateForm(__classid(TForm2), &Form2);
int n = ComboBox1->ItemIndex + 2; 	//  размерность массива
int leftl, topl, lefte, tope;  		//  положение колонки
int wtl, htl, wte, hte;     		//  размер колонки
wtl = Form2->ClientWidth/(n+1);
htl = Form2->ClientHeight/(n+1);
for(int i=0; i<=2; i++) {      		//  2 колонки
	leftl = 5;
	topl = 5;
	for (int j = 0; j <= n; j++) { 	//  по n строк в каждой
	lbl[i][j] = new TLabel (Form2);

	lbl[i][j]->Parent = Form2;	   	//  посадить кнопку на форму

	// настройка колонки
	lbl[i][j]->Left = leftl;
	lbl[i][j]->Top = topl;
	lbl[i][j]->Width = wtl;
	lbl[i][j]->Height = htl;
	lbl[i][j]->Caption = j;
		if ( i == 0) topl = topl + htl;
		else leftl = leftl + wtl;
	}
}
tope = 32;
wte = 480/n;
hte = 480/n;
for (int i = 1; i <= n; i++) {
	lefte = 32;
	for (int j = 1; j <= n; j++) {
		 edt[i][j] = new TEdit (Form2);
		 edt[i][j]->Parent = Form2;

		 //  настройка ячеек
		 edt[i][j]->Left = lefte;
		 edt[i][j]->Top = tope;
		 edt[i][j]->Width = wte;
		 edt[i][j]->Height = hte;
		 edt[i][j]->Font->Size = hte - 180/n;
		 edt[i][j]->MaxLength = 2;
		 // задать процедуру нажатия кнопки
		 edt[i][j]->OnKeyPress = EditKeyPress;
		 edt[i][j]->Tag = i*j;
		 lefte = lefte + wte;
	}
tope = tope + hte;
}
Form2->Show();
Form1->Hide();
}
//---------------------------------------------------------------------------

//  нажатие клавиши в поле редактирования
void __fastcall TForm1::EditKeyPress(TObject *Sender, char &Key)
{
TEdit *Edit;

Edit = (TEdit*)Sender;

if( (Key >='0') && (Key <= '9') )  //  цифра
	return;

if ( Key == VK_BACK)	//  клавиша <Backspace>
	return;

if (Key == VK_RETURN) //  нажатие клавиши Enter

	{
	if(StrToInt(Edit->Text) == Edit->Tag)
		Edit->Hide();
	else
		Application->MessageBoxA("Неправильно!","Ошибка",MB_ICONSTOP);
	return;
	}

//  остальные клавиши запрещены

Key = 0; //  не отображать символы
}
