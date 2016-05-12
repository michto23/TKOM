%{
#include <iostream>
using namespace std;
int mylineno = 0;
int comment_caller = 0;
%}

%option noyywrap
%x comment
%x w_tag
%x tresc_miedzy_tag
%x w_wartosc_atrybutu_1
%x w_wartosc_atrybutu_2

ws      	[ \t\n]+
slowo		[^ \t\n]+
tekst		[^<]*
excl_znaki_tekst	[<]
nazwa_taga	[A-Za-z_][^ \t\n>]*
atrybut_koncowy	([^ \t\n=>]+)">"
atrybut	(([^ \t\n=>]+)[=])
atrybut_bez_wart	(([^ \t\n=>]+))
otw_tag		("<"{nazwa_taga})|("<!DOCTYPE")
zak_tag		">"
cudzyslow_1	[^(\')]*[']
cudzyslow_2	[^(\")]*["]
start_wartosc_atr_1		"="{ws}*[']
start_wartosc_atr_2		"="{ws}*["]
wartosc_atrybutu_1		([^\n']+)(['])
wartosc_atrybutu_2		([^\n"]+)(["])
otw_zak_tag	[<][/]{nazwa_taga}
zak_otw_tag	[/][>]
doctype 	("<!DOCTYPE"|"<!doctype"){ws}"html"({slowo}|{ws})*">"

%%

{ws} { }

<INITIAL>"<!--"	{
						comment_caller = INITIAL;
						BEGIN(comment);
					}
<w_tag>"<!--"	{
						comment_caller = w_tag;
						BEGIN(comment);
					}
<tresc_miedzy_tag>"<!--"	{
						comment_caller = tresc_miedzy_tag;
						BEGIN(comment);
					}
<w_wartosc_atrybutu_1>"<!--"	{
						comment_caller = w_wartosc_atrybutu_1;
						BEGIN(comment);
					}
<w_wartosc_atrybutu_2>"<!--"	{
						comment_caller = w_wartosc_atrybutu_2;
						BEGIN(comment);
					}	
					
<comment>[^-]*        /* eat anything that's not a '*' */
<comment>"-"+"->"        BEGIN(comment_caller);






<INITIAL>{otw_tag}							{BEGIN(w_tag);	cout << "otw_tag - " << YYText() << '\n';}
<w_tag>{atrybut} 							{if (yyleng!=1) yyless(yyleng-1);cout << "atrybut - " << YYText() << '\n';}
<w_tag>{atrybut_bez_wart} 					{cout << "atrybut bez wartosci - " << YYText() << '\n';}
<w_tag>{start_wartosc_atr_1} 				{BEGIN(w_wartosc_atrybutu_1);cout << "start wartosci atrybutu 1 - " << YYText() << '\n';}
<w_tag>{start_wartosc_atr_2} 				{BEGIN(w_wartosc_atrybutu_2);cout << "start wartosci atrybutu 2 - " << YYText() << '\n';}
<w_wartosc_atrybutu_1>{wartosc_atrybutu_1}	{if (yyleng!=1) yyless(yyleng-1);cout << "wartosc atrybutu 1 - " << YYText() << '\n';}			
<w_wartosc_atrybutu_1>{cudzyslow_1} 			{BEGIN(w_tag);cout << "koniec wartosci atrybutu 1 - " << YYText() << '\n';} 
<w_wartosc_atrybutu_2>{wartosc_atrybutu_2}	{if (yyleng!=1) yyless(yyleng-1);cout << "wartosc atrybutu 2 - " << YYText() << '\n';}			
<w_wartosc_atrybutu_2>{cudzyslow_2} 			{BEGIN(w_tag);cout << "koniec wartosci atrybutu 2 - " << YYText() << '\n';}
<w_tag>{zak_tag}							{BEGIN(INITIAL);cout << "koniec tag - " << YYText() << '\n';}		
"<"								{cout << "znak wylaczony z tekstu - " << YYText() << '\n';}
<w_tag>{zak_otw_tag}						{BEGIN(INITIAL); cout << "zak_otw_tag - " << YYText() << '\n';}	
<INITIAL>{otw_zak_tag}						{BEGIN(w_tag);	cout << "otw_zak_tag - " << YYText() << '\n';}
<INITIAL>{tekst}  							cout << "tekst to - " << YYText() << '\n';

%%

