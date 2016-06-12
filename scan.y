%{
#include <iostream>
#include "/home/michto/Studia/TKOM/token/TokenType.h"
using namespace std;
int mylineno = 0;
int comment_caller = 0;
%}

%option noyywrap
%x comment
%x w_tag
%x wartosc_atrybutu_1
%x wartosc_atrybutu_2
%x w_skrypt

ws      	                [ \t\n]+
slowo		                [^ \t\n]+
tekst		                [^<]*
excl_znaki_tekst	        [<]
nazwa_taga	                [A-Za-z_][^ \t\n>]*
atrybut_koncowy	            ([^ \t\n=>]+)">"
atrybut	                    (([^ \t\n=>]+)[=])
atrybut_bez_wart	        (([^ \t\n=>]+))
otw_tag		                "<"{nazwa_taga}
otw_tag_doctype             "<"{doctype_txt}
zak_tag		                ">"
cudzyslow_1	                [^(\')]*[']
cudzyslow_2	                [^(\")]*["]
start_wartosc_atr_1		    "="{ws}*[']
start_wartosc_atr_2		    "="{ws}*["]
wartosc_atrybutu_1		    ([^\n']+)(['])
wartosc_atrybutu_2		    ([^\n"]+)(["])
otw_zak_tag	                [<][/]{nazwa_taga}
zak_otw_tag	                [/][>]
doctype 	                ("<!DOCTYPE"|"<!doctype"){ws}"html"({slowo}|{ws})*">"
doctype_txt	                [!][Dd][Oo][Cc][Tt][Yy][Pp][Ee]
script	                    [<][sS][cC][rR][iI][pP][tT][^<>]*[>]
script_koniec	            [<][/][sS][cC][rR][iI][pP][tT][>]
otw_tag_void                ([<][a][r][e][a])|([<][b][a][s][e])|([<][b][r])|([<][c][o][l])|([<][c][o][m][m][a][n][d])|([<][e][m][b][e][d])|([<][h][r])|([<][i][m][g])|([<][i][n][p][u][t])|([<][l][i][n][k])|([<][m][e][t][a])|([<][p][a][r][a][m])|([<][s][o][u][r][c][e])

%%

{ws} { }

<INITIAL>"<!--"	{
						comment_caller = INITIAL;
						BEGIN(comment);
					}
<w_skrypt>"<!--"	{
						comment_caller = w_skrypt;
						BEGIN(comment);
					}
					
<comment>[^-]*        /* eat anything that's not a '*' */
<comment>"-"+"->"        BEGIN(comment_caller);





<INITIAL>{script}							{BEGIN(w_skrypt);                       return TokenType::ScriptStart;}
<INITIAL>{otw_tag_void}                     {BEGIN(w_tag);                          return TokenType::StartTagVoid;}
<INITIAL>{otw_tag_doctype}                  {BEGIN(w_tag);                          return TokenType::StartTagDoctype;}
<INITIAL>{otw_tag}							{BEGIN(w_tag);	                        return TokenType::StartTag;}
<w_tag>{atrybut} 							{if (yyleng!=1) yyless(yyleng-1);       return TokenType::Attribute;}
<w_tag>{atrybut_bez_wart} 					{                                       return TokenType::AttributeNoValue;}
<w_tag>{start_wartosc_atr_1} 				{BEGIN(wartosc_atrybutu_1);             return TokenType::AttributeValueStartEqualsQuote;}
<w_tag>{start_wartosc_atr_2} 				{BEGIN(wartosc_atrybutu_2);             return TokenType::AttributeValueStartEqualsQuotes;}
<wartosc_atrybutu_1>{wartosc_atrybutu_1}	{if (yyleng!=1) yyless(yyleng-1);       return TokenType::AttributeValue;}
<wartosc_atrybutu_1>{cudzyslow_1} 			{BEGIN(w_tag);                          return TokenType::AtrributeValueEndQuote;}
<wartosc_atrybutu_2>{wartosc_atrybutu_2}	{if (yyleng!=1) yyless(yyleng-1);       return TokenType::AttributeValue;}
<wartosc_atrybutu_2>{cudzyslow_2} 			{BEGIN(w_tag);                          return TokenType::AtrributeValueEndQuotes;}
<w_tag>{zak_tag}							{BEGIN(INITIAL);                        return TokenType::EndTag;}
<w_tag>{zak_otw_tag}						{BEGIN(INITIAL);                        return TokenType::EndOnStartTag;}
<w_skrypt>{script_koniec}					{BEGIN(INITIAL);                        return TokenType::ScriptEnd;}
"<"											{                                       return TokenType::SpecialCharText;}
<w_skrypt>"<"								{                                       return TokenType::SpecialCharText;}
<INITIAL>{otw_zak_tag}						{BEGIN(w_tag);	                        return TokenType::StartOnEndTag;}
<w_skrypt>{tekst}  							{                                       return TokenType::Text;}
<INITIAL>{tekst}  							{                                       return TokenType::Text;}

%%
