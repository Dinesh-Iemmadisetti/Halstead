#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include<cmath>
#include<dirent.h>
#include<ios> 
#include<unistd.h>
//#include <windows.h>
using namespace std;

int  LoadKeywordFile(string ,vector< unordered_set <string> >& );
//global values;

ofstream outfile;
//ifstream operators_list;
int TotalCount=0;
int count_Lines=0;
int flowerL=0;
int flowerR=0;
int circleL=0;
int circleR=0;
int squareL=0;
int squareR=0;
int triangleL=0;
int triangleR=0;
int doubleQuo_counter=0;
int singleQuo_counter=0;
int n1=0,n2=0,N1=0,N2=0;
string CommWord="";
string SpecialDoubleQuo="\"";
string SpecialSingleQuo="\'";

int in=0;
vector<string>SP;

//void validateBrackets(unordered_set<string>);

//increment left and right flower bracket count;
void checkFlowerBrackets(char ch)
{
	if(ch=='{')
		flowerL++;
	else
		flowerR++;
}

//increment left and right circular bracket count;
void checkCircleBrackets(char ch)
{
        if(ch=='(')
	circleL++;
	else
	circleR++;
}

//increament left and right square bracket count;
void checkSquareBrackets(char ch)
{
	if(ch=='[')
	squareL++;
	else
	squareR++;

}

void checkTriangleBrackets(char ch)
{
	if(ch=='<')
	squareL++;
	else
	squareR++;
}


// check the single and qouble quotations is it finds a pair it will push into operators set
//if already present increases N1++
int QuoCount(unordered_set<string> *operands,string word,int quo)
{
		
		if(operands->empty())
		{
			

			 operands->insert(word);
			 n2++;
			 N2++;
			 return 1;
		}
		else
		{
			if(operands->find(word)!=operands->end())
			{
				n2 = n2 + quo;//new
				N2 = N2 + quo;
				return 1;
			}
			else
			{
				operands->insert(word);
				n2++;
				N2++;
				if(quo>1)
				{
					n2+=quo-1;//new
					N2+=quo-1;	
				}
				return 1;
			}
		}

		return 0;
}

//insertOper is only for operators it will check and insert the string into the operators set
//if already present , increases N1++;

int insertOperators(unordered_set<string> *operators,string word)
{

	if(operators->empty())
	{
		cout<<"push:"<<word<<endl;
		 operators->insert(word);
  		 n1++;
   		 N1++;
		 return 1;
     	}
      	else
       	{
        	if(operators->find(word)!=operators->end())
	 		{
				cout<<"push duplicate:"<<word<<endl;
	  			N1++;
				return 1;
	   		}	
	    	else
	     	{
				cout<<"push:"<<word<<endl;
	       		operators->insert(word);
	         	n1++;
		   		N1++;
				return 1;
			}
	}
	return 0;
}

void validateBrackets(unordered_set<string>* operators,unordered_set<string>* operands)
{
	if((doubleQuo_counter!=0)&&((doubleQuo_counter%2)==0))
	{
		int quo=doubleQuo_counter / 2;
		//QuoCount(operands,"\"\"",quo);
		SpecialDoubleQuo+="\"";//new
		QuoCount(operands,SpecialDoubleQuo,quo);//new
		doubleQuo_counter=0;
		SpecialDoubleQuo="\"";

	}

	if((singleQuo_counter!=0)&&((singleQuo_counter%2)==0))
	{
		int quo=singleQuo_counter / 2;
		SpecialSingleQuo+="\'";//new
		//QuoCount(operands,"''",quo);
		QuoCount(operands,SpecialSingleQuo,quo);//new
		singleQuo_counter=0;
		SpecialSingleQuo="\'";
	}

	if((flowerL!=0)&&(flowerL==flowerR))
	{
		insertOperators(operators,"{}");
		flowerL=flowerR=0;
	}

	if((circleL!=0)&&(circleL==circleR))
	{
		 insertOperators(operators,"()");
		circleL=circleR=0;
	}

	if((squareL!=0)&&(squareL==squareR))
	{
		 insertOperators(operators,"[]");
		squareL=squareR=0;
	}

	if((triangleL!=0)&&(triangleL==triangleR))
	{
		 insertOperators(operators,"<>");
		triangleL=triangleR=0;
	}

}


//check function check for each string given to it wether it's a operator or operand  
int check(unordered_set<string> *keys, unordered_set<string> *operators,unordered_set<string> *operands,string oneword)
{
cout<<"hey i'm inside check\n";
cout<<oneword<<":one_word\n";
	if(keys->find(oneword)!=keys->end())
	{
		return insertOperators(operators,oneword);
	}
	else
	{
		if(oneword!="" && oneword!=" ")
	 	{
			if(operands->empty())
			{
				operands->insert(oneword);
				n2++;
				N2++;
				return 1;
			}
			else
			{
	 			if(operands->find(oneword) != operands->end())
				{
	        			N2++;
					return 1;
				}
				else
				{
					cout<<oneword<<"before inserting operator\n";
					operands->insert(oneword);
					n2++;
					N2++;
					return 1;
               	}
			}
        }
		return 0;
	}

}

//all the not matched string are sent here to check them  char by char 
//depending it a number ,alphabet or symboles it will divide it and send to check; 
int notMatched(unordered_set<string> *keys,unordered_set<string> *operators,unordered_set<string> *operands,string sample)
{
	int ip=0;
	cout<<sample<<" in function\n";
	string word=sample;
	int d=0;
	cout<<word.length()<<":word length\n";
	for(unsigned int k=0;k<word.length();k++)
	{
		string oneword="";
		if(isalpha(word[k]))
		{
			do
			{
				if(k==word.length())
				break;
				oneword+=word[k];
				cout<<oneword<<":word\n";
				k++;
			}
			while(isalpha(word[k]) || isdigit(word[k]) || word[k]=='_'  || word[k]=='$');
		}

		/*	while(isalpha(word[k]))
			{
				if(k==word.length())
					break;
				oneword+=word[k];
				cout<<oneword<<":word\n";
				k++;
			}
		*/

		cout<<":out of alpha check\n";
		cout<<d<<" :d\n";

		if(!oneword.empty())
		 	d=check(keys,operators,operands,oneword);
		cout<<d<<":returned d\n";
		if(d==1)
		{
			k--;
			d=0;
			continue;
		}

		if(isdigit(word[k]) || word[k]=='-')
		{
			if((k<word.length()-1) && word[k]=='-' && !(isdigit(word[k+1])) )
			{
			}
			else
			{
				do
				{
					if(k==word.length())
						break;
					oneword+=word[k];
					cout<<oneword<<":word\n";
					k++;
				}
				while(isdigit(word[k]) || word[k]=='.');
			}
		}
		cout<<"out of digit\n";
		cout<<d<<" :d\n";
		if(!oneword.empty())
		d=check(keys,operators,operands,oneword);
		cout<<d<<":returned d\n";
		if(d==1)
		{
			k--;
			d=0;
			continue;
		}

		while(!(isalpha(word[k]) ^ isdigit(word[k])))
		{
			//	if(k==word.length())
			//		 break;
				if(word[k]=='_' || word[k]=='$')
				{
					do
					{
						if(k==word.length())
						break;
						oneword+=word[k];
						cout<<oneword<<":word\n";
						k++;
					}
					while(isalpha(word[k]) || isdigit(word[k]) || word[k]=='_'  || word[k]=='$' );
					check(keys,operators,operands,oneword);
					
				}

				else if((word[k]=='{')||(word[k]=='}'))
				{
					cout<<word[k]<<":inside {} if\n";
					checkFlowerBrackets(word[k]);
					ip++;
					break;
				}
				else if((word[k]=='(')|| (word[k]==')'))
				{
					cout<<word[k]<<":inside () if\n";

					checkCircleBrackets(word[k]);
					ip++;
					break;
				}
				else if((word[k]=='[')||(word[k]==']'))
				{
					cout<<word[k]<<":inside [] if\n";
					checkSquareBrackets(word[k]);
					ip++;
					break;
				}

				else if(word[k]==',')
				{
					if(oneword!="")
					{
						cout<<oneword<<":inside , if\n";
						check(keys,operators,operands,oneword);
					//	oneword="";
					}
					string one="";
					one+=word[k];
					cout<<one<<":inside ! if\n";
					check(keys,operators,operands,one);
					ip++;
					break;
					//goto End;

				}

				else if(word[k]=='.')
				{
					if(oneword!="")
					{
						cout<<oneword<<":inside , if\n";
						check(keys,operators,operands,oneword);
					}
				
					cout<<":inside . if\n";
					check(keys,operators,operands,".");
					ip++;
					break;
					//goto End;

				}

				else if(word[k]==';')
				{
					if(oneword!="")
					{
						cout<<oneword<<":inside ; if\n";
						check(keys,operators,operands,oneword);
					}
					cout<<":inside ; if\n";
					check(keys,operators,operands,";");
					ip++;
					break;
					//goto End;

				}

				else if(word[k]=='\'')
				{
					cout<<word[k]<<":inside ' if\n";
					if(k>0 && k<word.length())
					{
						if(word[k-1]=='\\')
						{
							ip++;
							break;
						}
					}
					singleQuo_counter++;
					//new
					cout<<"singleQuo_counter:"<<singleQuo_counter<<endl;
					if((singleQuo_counter!=0) && ((singleQuo_counter)%2!=0))
					{
						if(oneword!="")
						{
							cout<<oneword<<":inside  if\n";
							check(keys,operators,operands,oneword);
						}

						if(k<sample.length()-1)
						{
							string checkWord=sample.substr(k+1); //new
							//string checkQuoWord=sample.substr(k+1);
							string checkQuoWord=checkWord;

							Loop3:
							cout<<"checkQuoWord:"<<checkQuoWord<<":"<<endl;
							
							int endQuo = checkQuoWord.find('\'');

						  //	SpecialSingleQuo+=sample.substr(K+1,endQuo-1);

							cout<<"SpecialSingleQuo:"<<SpecialSingleQuo<<endl;

							cout<<"After find "<<":"<<checkQuoWord<<":"<<endl;
							if(endQuo!= -1)
							{
								checkQuoWord = checkQuoWord.substr(endQuo);//+1 

								cout<<"checkQword \' :"<<checkQuoWord<<endl;

								int posA=checkWord.length() - checkQuoWord.length() -1 ;
								cout<<"PosA :"<<posA<<endl;
								cout<<"checkWord[]:"<<checkWord[posA]<<endl;
								//sleep(10);
						        //cout<<"value:"<<sample[posA]<<endl;

								if(posA >= 0 && posA < checkWord.length()-1) //need to check 2 original
								{
									if(checkWord[posA]=='\\')
									{
										cout<<"checkWord before:"<<checkWord<<endl;
										checkWord = checkWord.erase(posA,2);	//new
										cout<<"checkWord after:"<<checkWord<<endl;

										checkQuoWord = checkQuoWord.substr(1);

										cout<<"checkQQWord:"<<checkQuoWord<<endl;
										k+=posA+2;
										cout<<"K:"<<k<<endl;
										//sleep(1000);

										goto Loop3;

									}
								}
								cout<<"endQuo:="<<endQuo<<endl;
								

								if(posA== -1)
								{
									k+=posA+2;
									SpecialSingleQuo += checkWord;

								}
								else
								{
									cout<<checkWord.substr(posA)<<endl;
									SpecialSingleQuo += checkWord.substr(0,posA+1);//new
									cout<<"ssQ:"<<SpecialSingleQuo<<endl;
									k+=posA+2;
								}

								//	word = sample.substr(1);	
								//else
								//	word = sample.substr(posA+2);
								
								ip++;
								singleQuo_counter++;//if(ch=='{')
								
								cout<<"cword"<<checkWord<<endl;
								sleep(10);
								cout<<"endQuo inside error:single_Counter"<<singleQuo_counter<<endl;
								validateBrackets(operators,operands);
								break;
							}
							else
							{
								SpecialSingleQuo += sample.substr(k+1);
								return 4;
							}
						}
						else
							return 4;
					}
					else
					{
						ip++;
						break;
					}
					//new 
					//ip++;
					//break;
				}

				else if(word[k]=='"')
				{

					cout<<word[k]<<":inside \" if\n";
					if(k>0 && k<word.length()-1)
					{
						/*	if(word[k-1]=='\'' && word[k+1]=='\'')
							{
								singleQuo_counter+=2;
								ip++;
								//k++;
								break;
							}
							
						else
						*/
						 
						if(word[k-1]=='\\')
						{
							ip++;
							break;
						}
					}
					doubleQuo_counter++;
					//new
					cout<<"doubleQuo_counter:"<<doubleQuo_counter<<endl;
					if((doubleQuo_counter!=0) && ((doubleQuo_counter)%2!=0))
					{
						if(oneword!="")
						{
							cout<<oneword<<":inside  if\n";
							check(keys,operators,operands,oneword);
						}
						if(k<sample.length()-1)
						{
							string checkWord=sample.substr(k+1);

							//string checkQuoWord=sample.substr(k+1);
							string checkQuoWord = checkWord;

							Loop4:
							cout<<":"<<checkQuoWord<<":"<<endl;
							
							int endQuo = checkQuoWord.find('"');
							cout<<"EndQ:"<<endQuo<<endl;
							cout<<"After find "<<":"<<checkQuoWord<<":"<<endl;
							if(endQuo!= -1)
							{
								checkQuoWord = checkQuoWord.substr(endQuo);
								int posA= checkWord.length() - checkQuoWord.length() -1;
								cout<<"checkWordQuo:"<<checkQuoWord<<endl;
								cout<<"PosA :"<<posA<<endl;
								//sleep(1000);
								cout<<":"<<checkWord[posA]<<":"<<endl;
								//sleep(1000);
								if(posA >= 0 && posA < checkWord.length()- 1)//-2
								{
									if(checkWord[posA]=='\\')
									{

										checkWord = checkWord.erase(posA,2);

										checkQuoWord = checkQuoWord.substr(1);

										k+=posA+2;

										goto Loop4;

									}
								/*	else if(sample[posA]=='\'' && sample[posA+2]=='\'')
									{
										checkQuoWord = checkQuoWord.substr(2);
										goto Loop4;
									}
								*/
								}

								if(posA== -1)
								{
									k+=posA+2;
									SpecialDoubleQuo += checkWord;
								}
								else
								{
									SpecialDoubleQuo += checkWord.substr(0,posA+1);//new
									cout<<"s:"<<SpecialDoubleQuo<<endl;
									k+=posA+2;
									cout<<checkWord.substr(posA)<<endl;
									cout<<"ssQ:"<<SpecialSingleQuo<<endl;
								}


								cout<<"endQuo:="<<endQuo<<endl;
								
								ip++;
								doubleQuo_counter++;
								//SpecialDoubleQuo += checkWord;
								cout<<"duoCword:"<<checkWord<<endl;
								cout<<"endQuo inside error:double_Counter"<<doubleQuo_counter<<endl;
								//sleep(100);
								validateBrackets(operators,operands);
								break;
							}
							else
							{
								SpecialDoubleQuo += checkWord;
								return 3;
							}
						}
						else
							return 3;
					}
					else
					{
						ip++;
						break;
					}
				}

				

				 //new

				/*  if(word[k]==';')
					{
						cout<<word[k]<<":inside ; if\n";
						string colan;
						colan+=word[k];
						check(keys,operators,operands,colan);
						ip++;
						break;
						
					}
				*/


				//new
				

				else if((k<word.length()-1) && (word[k]==word[k+1]))// // == ++
				{
					//new
					if(word[k]=='/')
					{
						if(k>0 && k < word.length() -2 )
						{
							if(word[k-1]=='\'' && word[k+2]=='\'')
							{
								singleQuo_counter++;
								k+=2;
								ip++;
								break;
							}
						}
						if(oneword!="")
						{
							cout<<oneword<<":inside  if\n";
							check(keys,operators,operands,oneword);
						}

						string LineComment;
						LineComment+=word[k];
						LineComment+=word[k+1];
						cout<<LineComment<<":inside {} if\n";
						//check(keys,operators,operands,LineComment);
						return 1;	
					}
					//new
					string one="";
					one+=word[k];
					one+=word[k+1];
					//if((k<word.length()-2) && word[k]== '=' && word[k+2]== '-' )
					//one+=word[k+2];
					cout<<one<<":inside double characters if\n";
					check(keys,operators,operands,one);
					k++;
					ip++;
					break;
				}

				else if((k<word.length()-1) && word[k]=='=' && word[k+1]!= '=') // =-
				{
					cout<<"oneword:"<<oneword<<endl;
					//		if(oneword!="")
					//		{
					//			cout<<oneword<<":inside = if\n";
					//			check(keys,operators,operands,oneword);
					//		}
					oneword+=word[k];
					check(keys,operators,operands,oneword);
					ip++;
					break;

				}

				else if( (k < word.length()-1)  && (word[k]=='!') && word[k+1]=='=')
				{
					if(oneword!="")
					{
						cout<<oneword<<":inside  != if\n";
						check(keys,operators,operands,oneword);
					}
					string one="";
					one+=word[k];
					one+=word[k+1];
					cout<<one<<":inside ! if\n";
					check(keys,operators,operands,one);
					k++;
					ip++;
					break;
				}

				else if( (k < word.length()-1)  && (word[k]=='*') && word[k+1]=='/')
				{
					if(oneword!="")
					{
						cout<<oneword<<":inside  != if\n";
						check(keys,operators,operands,oneword);
					}
					k++;
				}
				//new

				else if(word[k]=='<' || word[k]=='>')
				{

					if(oneword!="")
					{
						cout<<oneword<<":inside <> if\n";
						check(keys,operators,operands,oneword);
					}
					//oneword="";

					if( (k<word.length()-1) && word[k]=='<' && word[k+1]=='<')
					{
						check(keys,operators,operands,"<<");
						k++;
						ip++;
						break;
					}
					else if( (k<word.length()-1) && word[k]=='>' && word[k+1]=='>')
					{
						check(keys,operators,operands,">>");
						k++;
						ip++;
						break;
						//goto End;
					}
					else if( word[k]=='>')
					{
						check(keys,operators,operands,">");

						ip++;
						break;
			         //				oneword+=word[k];
					}
					else if( (k<word.length()-1) && word[k]=='<' && word[k+1]!='=')
					{
						check(keys,operators,operands,"<");
						ip++;
						break;

					}
				}

				else if((k<word.length()-1) && (word[k]=='/' && word[k+1]=='*'))
				{

					if(oneword!="")
					{
						cout<<oneword<<":inside  if\n";
						check(keys,operators,operands,oneword);
					}

					//check(keys,operators,operands,"/*");


					string checkCommWord=sample.substr(k);
					cout<<":"<<checkCommWord<<":"<<endl;


					int endComm = checkCommWord.find("*/");
					cout<<"endComm:="<<endComm<<endl;
					if(endComm!=-1)
					{
						k+=endComm+1;
						ip++;
						//check(keys,operators,operands,"*/");
						break;
					}
					else
					{
						return 2;

					}

				}
				//new
				else
				{

					oneword+=word[k];//
				//	cout<<word<<":word is\n";
				//	cout<<word.length()<<":length\n";
				//	cout<<k<<":k\n";
				//	cout<<oneword<<":word\n";

				}
			End:	
			k++;

			if(k==word.length())
			break;

		}
		if(ip==1)
		{
			cout<<ip<<": ip\n";
			ip=0;
			continue;
		}

		//cout<<"out of either\n";
		// cout<<d<<" :d\n";
		// cout<<oneword<<" out side either\n";

		if(!oneword.empty())
		d=check(keys,operators,operands,oneword);

	  //	cout<<d<<":returned d\n";
		if(d==1)
		{
			k--;
		//	cout<<"ater decrement\n";
			d=0;
			continue;
		}
	  //	cout<<k<<" end of for\n";
	}
	validateBrackets(operators,operands);
	return 0;
}

int checkCommentInWords(vector<string> AllWords, unsigned int& pos )
{
	int pos1=pos;
	pos1++;
	for(int i=pos1;i<AllWords.size();i++)
	{
		string Word = AllWords[i];
		if(Word.find("*/")!=-1)
		{
			int p=Word.find("*/");

			if(p<(Word.length()-2))
			{
				CommWord = Word.substr(p+2);
				pos=i;
				return -2;
			}
			return i;
		}
	}
		return -1;
}

int checkDoubleQuoPresence(vector<string> AllWords, unsigned int& pos)
{
	int pos1=pos;
	pos1++;
	for(int i=pos1;i<AllWords.size();i++)
	{
		//string sample=AllWords[i];

		string Word = AllWords[i];
		string checkWord= AllWords[i];

		cout<<endl<<"THE WORD :"<<Word<<endl;
		Loop1:
		cout<<":"<<Word<<":"<<endl;
		int p = Word.find('"');
		if(p!=-1)
		{
			cout<<endl<<"THE WORD :"<<Word<<endl;
			cout<<"Word:"<<Word<<endl;
			Word = Word.substr(p);
			cout<<"Word:"<<Word<<endl;
			int posA = checkWord.length() - Word.length() -1;
			cout<<"PosA :"<<posA<<endl;
			if(posA >= 0 && posA<checkWord.length()-1)
			{
				if(checkWord[posA]=='\\')
				{
					checkWord = checkWord.erase(posA,2);//new
					Word = Word.substr(1);
					goto Loop1;
				}
				else if( posA<checkWord.length()-2 && checkWord[posA]=='\'' && checkWord[posA+2]=='\'')
				{
						checkWord = checkWord.erase(posA,3);//new
						Word = Word.substr(2);
						goto Loop1;
				}
			}
			cout<<":="<<p<<endl;
		 //	cout<<sample.substr(posA)<<endl;

		 	if(posA== -1)
			{
				Word = checkWord.substr(1);
				checkWord = checkWord.erase(posA+1,1);	
				cout<<Word<<endl;
				//sleep(100);
			}
			else
			{
				Word = checkWord.substr(posA+2);
				SpecialDoubleQuo += checkWord.substr(0,posA+1);
			//	SpecialDoubleQuo += checkWord.substr(0,posA);
			}

			doubleQuo_counter++;
			cout<<"p inside  Double_Counter"<<doubleQuo_counter<<endl;
			if(Word.length() > 0 )
			{
				CommWord = Word;
				cout<<"CommWord:"<<CommWord<<endl;
				pos=i;
				
				return -2;
			}
			else 
				return i;
		}
		SpecialDoubleQuo += AllWords[i];
	}
	return -1;
}

//new
int checkSingleQuoPresence(vector<string> AllWords, unsigned int& pos)
{
	int pos1=pos;
	pos1++;
	int BreakLoopA=0;
	for(int i=pos1;i<AllWords.size();i++)
	{
		string sample=AllWords[i];
		string Word = AllWords[i];
		string checkWord= AllWords[i];
		cout<<endl<<"THE WORD :"<<Word<<endl;
		Loop3:
		cout<<":"<<Word<<":"<<endl;
		int p = Word.find('\'');
		if(p!=-1)
		{
			cout<<endl<<"THE WORD :"<<Word<<endl;
			cout<<"Word:"<<Word<<endl;
			Word = Word.substr(p);
			
			cout<<"Word:"<<Word<<endl;
			int posA=checkWord.length()-Word.length() -1;
			cout<<"PosA :"<<posA<<endl;
			if(posA >= 0 && posA<checkWord.length()-1)
			{
				if(checkWord[posA]=='\\')
				{
					Word = Word.substr(1);
					checkWord = checkWord.erase(posA,2);
					goto Loop3;
				}
			}
			cout<<":="<<p<<endl;
		 //	cout<<sample.substr(posA)<<endl;

			if(posA== -1)
			{
				Word = checkWord.substr(1);
				checkWord = checkWord.erase(posA+1,1);	
			}
			else
			{
				Word = checkWord.substr(posA+2);
				cout<<Word<<endl;
				//sleep(100);
				SpecialSingleQuo += checkWord.substr(0,posA+1);
				//SpecialSingleQuo += checkWord.substr(0,posA);
				
			}

			singleQuo_counter++;
			cout<<"p inside  single_Counter"<<singleQuo_counter<<endl;
			if(Word.length() > 0 )
			{
				
				CommWord = Word;
				cout<<"CommWord:"<<CommWord<<endl;
				pos=i;
				return -2;
			}
			else 
				return i;

		}
		SpecialSingleQuo += AllWords[i];
	}
	return -1;
}
//new

int checkCommentInLines(vector<string>& AllLines,int pos)
{

	for(int i=pos;i<AllLines.size();i++)
	{
		string Line = AllLines[i];
		if(Line.find("*/")!=-1)
		{
			int p=Line.find("*/");

			if(p<(Line.length()-2))
			{
				AllLines[i] = Line.substr(p+2);
			}
		//	if(p==Line.length() -2) //new
		//	{
		//		return i;
		//	}
	
		//	count_Lines--;

			return i;
		}
	//	count_Lines--;
	}
	return -1;
}


int checkDoubleQuoPresenceInLines(vector<string>& AllLines,int pos)
{
	for(int i=pos;i<AllLines.size();i++)
	{
		string Line = AllLines[i];
		cout<<endl<<"THE LINE :"<<Line<<endl;
		if(Line.find('"')!=-1)
		{
			cout<<endl<<"THE LINE :"<<Line<<endl;
			int p=Line.find('"');
			doubleQuo_counter++;

			if(p<(Line.length()-1))
			{
				AllLines[i] = Line.substr(p+1);
				SpecialDoubleQuo += Line.substr(0,p-1);

			}
		//	if(p==Line.length() -1)//new
		//	{
		//		return i+1;
		//	}
			return i;
		}
		else
		{
			SpecialDoubleQuo += AllLines[i];
		}
	}
	return -1;
}


//take the whole progaram in to a cyclometric vector and given to cyclometricComplex
//it will check each line present in the vector and calculate the cyclometric complexity
double cyclometricComplex(vector<string> cyclometric)
{
	vector<string> if_lines;
	int m,n;
	int yu=0;
	int if_count,elif_count,for_count,while_count,switch_count;
	if_count = elif_count = for_count = while_count = switch_count = 0;
	m=n=0;
	int Comment=0;
	int doubleCount = 0;
	int singleCount = 0;
	//string conditions[] = { "for" , "while" , "switch" , "else if","if" };
	string conditions[] = { "for" , "while" , "switch" ,"if" };
	//string conditions[] = { "if" };
	

	/*  for(unsigned int i=0 ; i<cyclometric.size() ; i++)
		{cout<< "HI\n";
		string line=cyclometric[i];
		cout<<"Line"<<line<<endl;
		}
	
	cout<<"------------------------------------------\n";
	for(unsigned int i=0 ; i<cyclometric.size() ; i++)
	{
		//cout<<"i:"<<i<<endl;
		string line=cyclometric[i];
		cout<<"LoopStart:"<<line<<endl;
	}
	cout<<"------------------------------------------\n";
	
	*/






	

	
	for(unsigned int i=0 ; i<cyclometric.size() ; i++)
	{
		cout<<"i:"<<i<<endl;
		string line=cyclometric[i];
		cout<<"LineStart:"<<line<<endl;

		Check:


		if( line.find('\'')!=-1 )
		{
			cout<<"singleCount:"<<singleCount<<endl;

			if(singleCount!=0)
			{
				int pos12;
				cout<<"line:"<<line<<endl;
				pos12=line.find('\'');
				cout<<"pos12"<<pos12<<endl;
				cout<<line[pos12-1]<<endl;
				if(pos12>0 && line[pos12-1]=='\\' )
				{
					//	line=line.substr(pos12+1);
					line.erase(pos12-1,2);
					cout<<line<<endl;	
					goto Check;				
				}
				singleCount--;
				cout<<"line length:"<<line.length()<<endl;
				if(pos12<line.length()-1)
				{
					cout<<"inside\n";
					//string sub1=line.substr(pos12+1);

					//line=sub1;
					//line=line
					line.erase(line.begin() + pos12);
					goto Check;
				}
				continue;
			}

			int pos13;
			pos13=line.find('\'');
			cout<<"pos13:"<<pos13<<endl;
				
			 //	singleCount++;
			 //	sleep(10000);
			if(pos13==0)
			{
				   // sleep(100);
					singleCount++;
					int pos14;
					string sub1=line.substr(pos13+1);
					if(sub1.find('\'')!=-1)
					{
						pos14=sub1.find('\'');
				//		singleCount--;
				//		if(pos14<sub1.length()-1)
				//		{
						//	string str=sub1.substr(pos14+1);
							sub1=sub1.substr(pos14);

							//new
								
							int posA=line.length() - sub1.length() -1;
							cout<<"posA:"<<posA<<endl;
							cout<<line[posA]<<endl;
							if(posA >= 0 && posA < line.length() -1)
							{
								if(line[posA]=='\\')
								{
									cout<<"here\n";
									sub1 = sub1.substr(1);
									if(sub1.find('\'')!= -1)
									{
										line=sub1;
										goto Check;
									}
								}
							}
							singleCount--;
							if(pos14<line.length()-1)
							{
								sub1=sub1.substr(1);
								line=sub1;
						//		cout<<"inside:\'"<<line<<endl;
						//		cout<<"single"<<singleCount<<endl;
								goto Check;
							}
						if(pos14 == line.length()-1)
							continue;
					}
					else
						continue;
			}
			else if(line[pos13-1] == '\\')
			{
				line.erase(pos13-1,2);	
				cout<<"eraser line:"<<line<<endl;
				goto Check;

			}
			else
			{ 	
				singleCount++;

				string subS=line.substr(0,pos13);
				cout<<"subS:"<<subS<<endl;
				int pos15;
				string first=line.substr(pos13+1);
					
				if(first.find('\'')!=-1)
				{
					pos15 = first.find('\'');
					first=first.substr(pos15);

					cout<<"first:"<<first<<endl;

					cout<<"pos15:"<<pos15<<endl;

					int posA=line.length() - first.length() -1;
					cout<<"posA:"<<posA<<endl;
					cout<<line[posA]<<endl;

					if(posA >= 0 && posA < line.length() -1)
					{
						if(line[posA]=='\\')
						{
							cout<<"here\n";
							first = first.substr(1);
							if(first.find('\'')!= -1)
							{
								line=subS+first;
								goto Check;
							}
								//	line=subS+first;
								//	goto Check;
						}
					}
					singleCount--;
					if(pos15<line.length()-1)
					{
						string str=first.substr(1);
						line = subS+" "+str;
						cout<<"inside:\':"<<line<<endl;
						cout<<"single"<<singleCount<<endl;
						goto Check;
					}
					if(pos15 == line.length()-1)
						continue;
				}
				singleCount--;
				line=subS;
			}
		}
		else if( line.find('"')!=-1 )
		{
			cout<<"DoubleCount:"<<doubleCount<<endl;
			if(doubleCount!=0)
			{
				cout<<"Line:"<<line<<endl;
				int pos11;
				pos11=line.find('"');
				if(pos11>0 && line[pos11-1]=='\\' )
				{
					//line=line.substr(pos11+1);
					line.erase(pos11-1,2);	
					cout<<line<<endl;
					goto Check;				
				}
				doubleCount--;
				
				if(pos11<line.length()-1)
				{
				//	string sub1=line.substr(pos11+1);
				//	line=sub1;
					line.erase(line.begin() + pos11);
					goto Check;
				}
				continue;
			}
				Dinesh:
				int pos6;
				pos6=line.find('"');
				//doubleCount++;
				if(pos6 == 0)
				{
					doubleCount++;
					int pos9;
					string sub1=line.substr(pos6+1);
					cout<<"Sub1 zero :"<<sub1<<endl;
					if(sub1.find('"')!=-1)
					{
						//sleep(10);
						pos9=sub1.find('"');
						sub1=sub1.substr(pos9);
						cout<<"Sub1 zero :"<<sub1<<endl;
							//new
						int posA=line.length() - sub1.length() -1;
						cout<<"posA:"<<posA<<endl;
						cout<<line[posA]<<endl;
						if(posA >= 0 && posA < line.length() -1)
						{
							if(line[posA]=='\\')
							{
								cout<<"here in zero \n";
								sub1 = sub1.substr(1);
								if(sub1.find('\'')!= -1)
								{
									line=sub1;
									goto Check;
								}
							}
						}
						doubleCount--;
						if(pos9<line.length()-1)
						{
							sub1=sub1.substr(1);
							line=sub1;
							cout<<"inside zero:\" "<<line<<endl;
							cout<<"double zero"<<singleCount<<endl;
							//sleep(1000);
							goto Check;
						}
							//new
						if(pos9 == line.length()-1)
							continue;
					}
					else
						continue;
				}

				else if(line[pos6-1] == '\\')
				{
					line.erase(pos6-1,2);	
					cout<<"eraser line:"<<line<<endl;
					goto Check;
				}

				else if(pos6 !=-1)
				{
					doubleCount++;
					string subS=line.substr(0,pos6);
					int pos10;
					cout<<"subsDo:"<<subS<<endl;
					string first=line.substr(pos6+1);
					if(first.find('"')!=-1)
					{
						pos10 = first.find('"');
						first=first.substr(pos10);
						cout<<"firstDuo:"<<first<<endl;

						int posA= line.length() - first.length() -1;
						cout<<"pos10:"<<pos10<<endl;
						cout<<"posA:"<<posA<<endl;
						cout<<"Value:"<<line[posA]<<endl;
						if(posA >= 0 && posA < line.length()-1 )
						{
							if(line[posA]=='\\')
							{
								first = first.substr(1);
								line=subS+first;
								goto Dinesh;
						//		goto Check;
							}
						}
						doubleCount--;
						if(pos10<line.length()-1)
						{
							string str=first.substr(1);
							line = subS+" "+str;
							cout<<"inside\":"<<line<<endl;
							cout<<"double"<<doubleCount<<endl;
							goto Check;
						}
						if(pos10 == line.length()-1)
							continue;
					}
					line=subS;
				}
				else
				{
					goto Check;
				}
		}

		else if(line.find("/*")!=-1 && Comment == 0)
		{
			cout<<"Inside /* \n";
			cout<<"Comment inside /*:"<<Comment<<endl;
			Comment++;
			int pos2;
			pos2=line.find("/*");
			if(pos2==0)
			{
				int pos3;
				if(line.find("*/")!=-1)
				{
					pos3=line.find("*/");
					Comment--;
					if(pos3<line.length()-2)
					{
						string str=line.substr(pos3+2);
						line = str;
						goto Check;
					}
					if(pos3 == line.length()-2)
						continue;
				}
				else
					continue;
			}
			else
			{
				string subS=line.substr(0,pos2);
				if(subS.find("*/")!=-1)
				{
					Comment--;
					goto Final;
				}
				int pos5;
				if(line.find("*/")!=-1)
				{
					pos5 = line.find("*/");
					Comment--;

					if(pos5<line.length()-2)
					{
						string str=line.substr(pos5+2);
						line = subS+" "+str;
						goto Check;
					}
					if(pos5 == line.length()-2)
						continue;
					
				}
				line=subS;
			}
		}
		else if(Comment!=0)
		{
			cout<<"Inside */ \n";
			cout<<"Comment inside */:"<<Comment<<endl;
			int pos4;
			if(line.find("*/")!=-1)
			{
				pos4=line.find("*/");
				Comment--;
				if(pos4<line.length()-2)
				{
					string str=line.substr(pos4+2);
					line = str;
					goto Check;
				}
				if(pos4 == line.length()-2)
						continue;
			}
			else
				continue;
		}

		if(line.find("//")!=-1 && Comment==0 )
		{
			cout<<"Inside // \n";
			string subS="";
			int pos;
			pos=line.find("//");
			
			if(pos==0)
				continue;
			else if(pos>0 && pos< line.length()-2)
			{
				if(line[pos-1]=='\'' && line[pos+2]=='\'')
				{
					cout<<"Line did't changed\n";
				}
				else
				{
				 	subS=line.substr(0,pos);
					line = subS;
					goto Check;
				}
			}
			else
			{
				subS=line.substr(0,pos);
				line = subS;
				goto Check;
			}
		}

		cout<<"SINGLE"<<singleCount<<endl;
		cout<<"DOUBLE"<<doubleCount<<endl;
		Final:
		cout<<"--------------------\n";
		cout<<"The Line :"<<line<<endl;
		cout<<" Comment Count:"<<Comment<<endl;

		//	for(int i=0;i<line.length();i++)
		//	{
		//		cout<<endl<<line[i]<<":"<<(int)line[i]<<endl;
		//	}

		/*	while(1)
			{
				if(line[0]==' ' && line.length() > 1)
				{
					line=line.substr(1);
				}
				else
					break;
			}
		*/
		cout<<"The Line after filter :"<<line<<endl;

		for(string k: conditions)
		{
			int Count=0;
			if( line.find(k)!=-1 )
			{
				cout<<"inside cyc\n";
				int subPos=line.find(k);

				if(subPos > 0 )
				{
					int y=0;
					line = line.substr(subPos-1);
					while(1)
					{
						if(line[0]==' ' && line.length() > 1)
						{
							line=line.substr(1);
						}
						else
						{
							y=1;
							break;
						}
					}
					if(y==1)
					{
						y=0;
						continue;	
					}
				}
				else
					line = line.substr(subPos);

				cout<<"LineInside:"<<line<<endl;
				for(int i=0;i<line.length();i++)
				{														//ifrk
					if(line.find(k)!=-1)
					{

						int pos7=line.find(k); 
						cout<< "HIII:"<<(int)line[pos7 -1]<<endl;
						cout<< pos7+k.length() - 1<<endl;
						cout<<line.length()<<endl;
						if(pos7 > 0 && (pos7+k.length() - 1) < line.length() )
						{
							cout<<"first if\n";
							int op=pos7+k.length();
							cout<<"value op:"<<line[op]<<endl;
							//if( (!(isalpha(line[pos7-1]) ^ isdigit(line[pos7-1])))  && ( (!(isalpha(line[op]) ^ isdigit(line[op]))) || (line[line[op]]==' ') )  )
							if( !(isalpha(line[pos7-1]) ^ isdigit(line[pos7-1]))  && ( !(isalpha(line[op]) ^ isdigit(line[op])) && ( line[op]==' ' || line[op]=='(' ) )  )
							{
								Count++;
							}

						}
						else if(pos7==0  && pos7+k.length() == line.length() )
						{
							cout<<"third if\n";
							if(k=="if")
							{
								if_count++;
								if_lines.push_back(line);

							}
							else if(k == "else if")
								elif_count++;
							else if(k == "while")
								while_count++;
							else if(k == "for")
								for_count++;
							else if(k=="switch")
								switch_count++;
							Count++;
						}
						else if(pos7==0  &&  (pos7+k.length() - 1)<line.length() )
						{
							cout<<"second if\n";
							int op1 = pos7+k.length();
							cout<<"value op1:"<<line[op1]<<endl;
							if(  !(isalpha( line[op1] ) ^ isdigit(line[ op1])) && ( line[op1]==' ' || line[op1]=='(' ) ) 
							{
								Count++;
								if(k=="if")
								{
									if_count++;
									if_lines.push_back(line);
								}
								else if(k == "else if")
									elif_count++;
								else if(k == "while")
									while_count++;
								else if(k == "for")
									for_count++;
								else if(k=="switch")
									switch_count++;
							}
						}
						
						
						
						line =line.substr(pos7 + k.length());
						cout<<line;
						i=-1;
						cout<<i<<endl;
						cout<<"CycCount:"<<Count<<endl;
					//	cout<<"ALLCount:"<<n<<endl;
					}

				}
				n +=Count;
				cout<<"ALLCount:"<<n<<endl;
				cout<<"if:"<<if_count<<endl;
				cout<<"else if:"<<elif_count<<endl;
				cout<<"while:"<<while_count<<endl;
				cout<<"for:"<<for_count<<endl;
				cout<<"switch:"<<switch_count<<endl;
				
			}
		}
	
	}
	m = n+1;
	for(int r=0;r < if_lines.size();r++)
	{
		cout<<r+1<<"If Lines :"<<if_lines[r]<<endl;
	}

	return (double) m;
}

//it will take a file and check fro n1,n2,N1,N2

int filterTheLine(string eachLine,vector<string>& each_word,vector<string>& cyclometric)
{
				string lineone;
				lineone = eachLine;
				if((lineone.compare("")==0) || (lineone.compare(" ")==0) || (lineone.compare("	")==0))//tab spaces
				{
					//continue;
					return -1;
				}
				//	cout<<lineone<<"$->"<<endl;
				string word;
				string line_inside=lineone;
				int pos=0;
				int first=0;
				while(1)
				{
					pos=line_inside.find(13);//remove \r
					if(pos!=-1)
						line_inside.erase(line_inside.begin() + pos);
					else
						break;
				}
				while(1)
				{
					pos=line_inside.find(9);//remove tab
					if(pos!=-1)
						line_inside.erase(line_inside.begin() + pos);
					else
						break;
				}
				//	cout<<":"<<line_inside<<":first line tab\n";
				while(1)
				{
					pos=line_inside.find(-62);
			  		if(pos!=-1)
			   			line_inside.erase(line_inside.begin() + pos);
			   	 	else
			     		break;
				}
				//		cout<<":"<<line_inside<<":first line -62\n";
				while(1)
				{
					pos=line_inside.find(-96);
			  		if(pos!=-1)
			   			line_inside.erase(line_inside.begin() + pos);
			    	else
			     		break;
				}

				//for "else if" if needed 

				/*
					while(1)
					{	
						pos=line_inside.find("else if");
						if(pos!=-1)
							line_inside.insert(pos+5,"-");
							//line_inside.erase(line_inside.begin() + pos);
						else
							break;

					}
				*/

				//	cout<<":"<<line_inside<<":first line -96\n";
				
            	if(line_inside[0]==' ')//only first space remove
            	{
                	//    cout<<line_inside.length()<<"\n";
                    int i=0;
                    for(;line_inside[i];i++)//count the all spaces
                    {
                   //     cout<<line_inside[i];
                        if(line_inside[i]!=' ')
                        {
                                break;
                        }

                    }
            		//    cout<<i<<endl;
                    while(i)
                    {
                        line_inside.erase(line_inside.begin()+0);
                        i--;
                    }
            	}
          		//              cout<<":"<<line_inside<<":final line\n";
                if(line_inside=="")
                {
            		//                    cout<<"inside here\n";
					return -1;
                    //continue;
                }



				//==================
                count_Lines++;//count each proper line;
				//==================




			//	if((line_inside.find("main()")!=-1) || in==1)//to count cyclometriccomplexity from main
			//	{
			//		in=1;cyclometric.push_back(line_inside);
			//	}
				cyclometric.push_back(line_inside);//count cyclometricComplxity from start of the program


				while(1)
				{
					pos = line_inside.find(' ');//check words in a line
					if(pos==-1)
						break;
					word=line_inside.substr(first,pos);
					if(word!="")
						each_word.push_back(word);
					line_inside=line_inside.substr(pos+1);
				}
				if(line_inside!="")
				{
					each_word.push_back(line_inside);
				}
		return 0;

}

int CheckLimits( vector<double> Value)
{
	string strline;
	ifstream readConfig;
			readConfig.open("./configuration.txt",ios::in);

			if(readConfig.is_open())
				cout<<"opened config File\n";
			else
			{
				cout<<"Config file did't opend\n";
				return 0;
			}
			
			for(int a=0;!readConfig.eof();a++)
			{
				
				string word;
				double max=0;
				double min=0;
				getline(readConfig,strline);
				cout<<"strline"<<strline<<endl;
				if((strline.length())>0)
				{
					while(1)
					{
						try
						{
							word=strline.substr(0,strline.find('|'));
							cout<<word<<endl;
							strline=strline.substr(strline.find('|') + 1);

							max = stoi( strline.substr( 0,strline.find('|') ) );
							cout<<max<<endl;
							strline=strline.substr(strline.find('|') + 1);

							min = stoi( strline.substr( 0,strline.find('|') ) );
							cout<<min<<endl;
							if(Value[a] >= min && Value[a] <= max)
							{
								outfile<<Value[a]<<",";
							}
							else if(Value[a] < min)
							{
								//min color
								outfile<<Value[a]<<",";

							}
							else
							{
								//max colour
							//	cout << "\033[1;31m bold red text \033[0m\n";
								outfile<<Value[a]<<",";
							}
							break;
						}
						catch(invalid_argument f)
    					{
							cout<<"invalid conversion\n";
							break;
    					}
					}
				
				}

			}
			readConfig.close();
	return 1;
}


/*	int Caliculation(int n1 ,int n2 ,int N1,int N2,vector<string> cyclometric,string en1,string en2,unordered_set<string> operators,unordered_set<string> operands)
	{
				vector<double> Value;
				cout<<"n1 = "<<n1<<endl;
				cout<<"n2 = "<<n2<<endl;
				cout<<"N1 = "<<N1<<endl;
				cout<<"N2 = "<<N2<<endl;
				double Program_length = N1 + N2;
				double Program_vocabulary = n1+n2;
				double volume = Program_length * (log2(Program_vocabulary));
				double difficulty = (double(n1)/2) * (double(N2)/double(n2));
				//double level = (1/difficulty);
				double effort = volume * difficulty;
				double Estimated_Length = n1*log2(n1)+n2*log2(n2);
				double Time_required_to_program = effort/18;
				//double Number_of_delivered_bugs = ((pow(effort,(2/3)))/3000);
				double Number_of_delivered_bugs = volume/3000;
				double Cyclometric=cyclometricComplex(cyclometric);
				TotalCount+=count_Lines;
				Value.push_back(Program_length);
				Value.push_back(Program_vocabulary);
				Value.push_back(volume);
				Value.push_back(difficulty);
				Value.push_back(effort);
				Value.push_back(Estimated_Length);
				Value.push_back(Time_required_to_program);
				Value.push_back(Number_of_delivered_bugs);
				Value.push_back(Cyclometric);

				ifstream readConfig;
				readConfig.open("./configuration.txt",ios::in);

				if(readConfig.is_open())
					cout<<"opened config File\n";
				else
				{
					cout<<"Config file did't opend\n";
					return 1;
				}
				outfile<<en1<<","<<n1<<","<<n2<<","<<N1<<","<<N2<<",";
				for(int a=0;!readConfig.eof();a++)
				{
					string strline;
					string word;
					double max=0;
					double min=0;
					getline(readConfig,strline);
					cout<<"strline"<<strline<<endl;
					if((strline.length())>0)
					{
						while(1)
						{
							try
							{
								word=strline.substr(0,strline.find('|'));
								cout<<word<<endl;
								strline=strline.substr(strline.find('|') + 1);

								max = stoi( strline.substr( 0,strline.find('|') ) );
								cout<<max<<endl;
								strline=strline.substr(strline.find('|') + 1);

								min = stoi( strline.substr( 0,strline.find('|') ) );
								cout<<min<<endl;
								if(Value[a] >= min && Value[a] <= max)
								{
									outfile<<Value[a]<<",";
								}
								else if(Value[a] < min)
								{
									//min color
									outfile<<Value[a]<<",";

								}
								else
								{
									//max colour
								//	cout << "\033[1;31m bold red text \033[0m\n";
									outfile<<Value[a]<<",";
								}
								break;
							}
							catch(invalid_argument f)
							{
								cout<<"invalid conversion\n";
								break;
							}
						}
					
					}

				}
				readConfig.close();
				//sleep(100);

				outfile<<count_Lines<<","<<en2<<endl;
				//outfile<<en2<<","<<en1<<","<<n1<<","<<n2<<","<<N1<<","<<N2<<","<<Program_length<<","<<Program_vocabulary<<","<<volume<<","<<difficulty<<","<<effort<<","<<Estimated_Length<<","<<Time_required_to_program<<","<<Number_of_delivered_bugs<<","<<count_Lines<<","<<Cyclometric<<","<<endl;
				cout << "Program_length : " << Program_length << endl;
				cout << "program vocabulary : " << Program_vocabulary << endl;
				cout << "Volume : " << volume << endl;
				cout << "Difficulty : " << difficulty << endl;
				//cout << "Level : " << level << endl;
				cout << "Effort : " << effort << endl;
				cout << "Estimated_Length :"<<Estimated_Length <<endl;
				cout << "Time_required_to_program :"<<Time_required_to_program<<"(sec)"<<endl;
				cout << "Number_of_delivered_bugs :"<<Number_of_delivered_bugs<<endl;
				cout << "Number of lines in the codes:"<<count_Lines<<endl;
				//count_Lines=0;
				cout << "Cyclometric Complexcity :"<<Cyclometric<<endl;
				unordered_set<string>::iterator itr1,itr2;
				cout<<"operators\n";
				for(itr1=operators.begin();itr1!=operators.end();itr1++)
									cout << (*itr1) << endl;
				cout<<"===========================================\n";
				cout<<"operands\n";
				for(itr2=operands.begin();itr2!=operands.end();itr2++)
									cout << (*itr2) << endl;
				cout<<"===========================================\n";
				flowerL=0;
				flowerR=0;
				circleL=0;
				circleR=0;
				squareL=0;
				squareR=0;
				doubleQuo_counter=0;
				singleQuo_counter=0;
				n1=0,n2=0,N1=0,N2=0;
				count_Lines=0;
				SpecialDoubleQuo="\"";
				SpecialSingleQuo="\'";

		return 1;
	}
*/
int checkValuesOfThefile(string dir_path,string en1,unordered_set<string> &keywords)
{
			ifstream myfile;
			string en2=dir_path+en1;//allfies/a.cpp
			cout<<en2<<" file path\n";
 			myfile.open(en2,ios::in);

			if(myfile.is_open())
			{

				cout<<"opened\n";
            }
			else
			{
				cout<<"file did't opend\n";
				return 1;
				//	return 1;
			}
			//	ifstream operators_list;


			//========================
			//int count_lines=0;//to count lines
			//========================


			//	cout<<"here"<<endl;
			//	operators_list.open("key_words.txt",ios::in);
		 //	cout<<"here"<<endl;
			unordered_set<string> operators;
			unordered_set<string> operands;
			vector<string> cyclometric;
			string strline;
			//	vector<char> line;
			vector<string> eachLine;//call to each line
			//	unordered_set<char> distinct;
			//	int ko=1;
		 //	cout<<"here2"<<endl;
			while(!myfile.eof())
			{

             //				cout<<"here3"<<endl;
				getline(myfile,strline);
             //				cout<<"here4"<<endl;
				 //get line push into the string line
					//		cout<<ko<<":"<<strline<<endl;
					//		ko++;
					/*	char ch;
					for(unsigned int i=0;i<strline.length();i++)
					{
						ch=strline[i];
						line.push_back(ch);
					}*/

				if((strline.length())>0)
				{
				//	cout<<"here5"<<endl;
					eachLine.push_back(strline);//take each line push in the vector
				}

			}

			/*	 for(unsigned int i=0;i<line.size();i++)
	 		{
	 			if(line[i]=='\n')
				cout<<endl;

				int z=line[i];
				cout<<line[i];
				cout<<":"<<z<<endl;
	 		}
			*/
			
			in = 0;
			for(unsigned int i=0;i<eachLine.size();i++)//each line in the file
			{
				cout<<"========\n||n1 ="<<n1<<"\n========"<<endl;
				cout<<"========\n||N1 ="<<N1<<"\n========"<<endl;


				cout<<"========\n||n2 ="<<n2<<"\n========"<<endl;
				cout<<"========\n||N2 ="<<N2<<"\n========"<<endl;

				vector<string> each_word;
				int value = filterTheLine(eachLine[i],each_word,cyclometric);
				if(value==-1)
					continue;
				cout<<"Count Lines :"<<count_Lines<<endl;
				for(unsigned int j=0;j<each_word.size();j++)
				{
					cout<<each_word[j]<<"$<-\n";
					string search=each_word[j];
					if(j==0 && search.length() >= 2)
					{
						if(search[0]=='/' && search[1]=='/' )
						{
							count_Lines--;
							break;
						}
						else if(search[0]=='/' && search[1]=='*')
						{
							string OneLine="";
							for(int f=0;f<each_word.size();f++)
							{
								OneLine+=each_word[f];
							}
							int postion=OneLine.find("*/");
							if(postion==-1)
							{
								count_Lines--;
							//	break;//new

							}
							else
							{

								if(postion<(OneLine.length()-2))
								{
									
									//CommWord = Word.substr(p+2);

								}
								else
								{
									count_Lines--;
								}

							}
						}
						else if(search[0]=='*' && search[1]=='/')
						{
							count_Lines--;
							break;
						}
						
					}

					CommWord=search;

					//	cout<<search<<"search\n";
					if(keywords.find(search)!= keywords.end())
					{
					//		cout<<"operators area\n";
						insertOperators(&operators,search);
					}
					else
					{
						int op=0;
						//		cout<<"not matched area \n";
						while(1)
						{
							int result;
							result=notMatched(&keywords,&operators,&operands,CommWord/*search*/);
							if(result==0)
							{
								break;
							}
							else if(result==1)
							{
								op=1;
								break;
							}
							else if(result==2)
							{
								int h=0;
								if(j==each_word.size()-1)
									h=-1;
								else
									 h=checkCommentInWords(each_word,j);
								if(h!=-1)
								{
									//check(&keywords,&operators,&operands,"*/");
									//j=h;
									if(h==-2)
										continue;
									else 
									{
										j=h;
										break;
									}
								}
								else
								{
									int g=0;
									if(i==eachLine.size()-1)
										g=-1;
									else
										g=checkCommentInLines(eachLine,i+1);
									if(g!=-1)
									{
										//check(&keywords,&operators,&operands,"*/");
										i=g-1;
										op=1;
										break;
									}
								}
							}
							else if(result==3)
							{
								cout<<"here condition 3\n";
								int p=0;
								if(j==each_word.size()-1)
									p=-1;
								else
									p=checkDoubleQuoPresence(each_word,j);
								if(p!=-1)
								{
								//	j=p;
									if(p==-2)
										continue;
									else
									{
										j=p;
									break;
									}
								}
								else
								{
									int q=0;

									if(i==eachLine.size()-1)
										q=-1;
									else
										q=checkDoubleQuoPresenceInLines(eachLine,i+1);
									if(q!=-1)
									{
										i=q-1;
										op=1;
										break;
									}
								}

							}
							else if(result==4)
							{
								cout<<"Condition 4 \n";
								int r=0;
								if(j==each_word.size()-1)
									r=-1;
								else
									r=checkSingleQuoPresence(each_word,j);

								if(r!=-1)
								{
									if(r==-2)
										continue;
									else
									{
										j=r;
									break;
									}
								}
							}
						}

						validateBrackets(&operators,&operands);

						if(op==1)
						{
							op=0;
							break;
						}
					}
				}
			}

	//		int result = Caliculation(n1,n2,N1,N2,cyclometric,en1,en2,operators,operands);
	//		if(result==1)
	//			cout<<"successful\n";
	//		else
	//			cout<<"error\n";
					vector<double> Value;
					cout<<"n1 = "<<n1<<endl;
					cout<<"n2 = "<<n2<<endl;
					cout<<"N1 = "<<N1<<endl;
					cout<<"N2 = "<<N2<<endl;
					int Program_length = N1 + N2;
					int Program_vocabulary = n1+n2;
					double volume = Program_length * (log2(Program_vocabulary));
					double difficulty = (double(n1)/2) * (double(N2)/double(n2));
					//double level = (1/difficulty);
					double effort = volume * difficulty;
					double Estimated_Length = n1*log2(n1)+n2*log2(n2);
					double Time_required_to_program = effort/18;
					//double Number_of_delivered_bugs = ((pow(effort,(2/3)))/3000);
					double Number_of_delivered_bugs = volume/3000;
					double Cyclometric=cyclometricComplex(cyclometric);
					TotalCount+=count_Lines;
					outfile<<en1<<","<<n1<<","<<n2<<","<<N1<<","<<N2<<",";
					
					Value.push_back(Program_length);
					Value.push_back(Program_vocabulary);
					Value.push_back(volume);
					Value.push_back(difficulty);
					Value.push_back(effort);
					Value.push_back(Estimated_Length);
					Value.push_back(Time_required_to_program);
					Value.push_back(Number_of_delivered_bugs);
					Value.push_back(Cyclometric);
					int result=CheckLimits(Value);
					if(result==1)
						cout<<"successful\n";
					else
					{
						cout<<"error\n";
						exit(1);
					}
						
					outfile<<count_Lines<<","<<en2<<endl;
					//outfile<<en1<<","<<n1<<","<<n2<<","<<N1<<","<<N2<<","<<Program_length<<","<<Program_vocabulary<<","<<volume<<","<<difficulty<<","<<effort<<","<<Estimated_Length<<","<<Time_required_to_program<<","<<Number_of_delivered_bugs<<","<<count_Lines<<","<<Cyclometric<<","<<en2<<endl;
					//outfile<<en2<<","<<en1<<","<<n1<<","<<n2<<","<<N1<<","<<N2<<","<<Program_length<<","<<Program_vocabulary<<","<<volume<<","<<difficulty<<","<<effort<<","<<Estimated_Length<<","<<Time_required_to_program<<","<<Number_of_delivered_bugs<<","<<count_Lines<<","<<Cyclometric<<","<<endl;
					cout << "Program_length : " << Program_length << endl;
					cout << "program vocabulary : " << Program_vocabulary << endl;
					cout << "Volume : " << volume << endl;
					cout << "Difficulty : " << difficulty << endl;
					//cout << "Level : " << level << endl;
					cout << "Effort : " << effort << endl;
					cout << "Estimated_Length :"<<Estimated_Length <<endl;
					cout << "Time_required_to_program :"<<Time_required_to_program<<"(sec)"<<endl;
					cout << "Number_of_delivered_bugs :"<<Number_of_delivered_bugs<<endl;
					cout << "Number of lines in the codes:"<<count_Lines<<endl;
					//count_Lines=0;
					cout << "Cyclometric Complexcity :"<<Cyclometric<<endl;
					unordered_set<string>::iterator itr1,itr2;
					cout<<"operators\n";
					for(itr1=operators.begin();itr1!=operators.end();itr1++)
										cout << (*itr1) << endl;
					cout<<"===========================================\n";
					cout<<"operands\n";
					for(itr2=operands.begin();itr2!=operands.end();itr2++)
										cout << (*itr2) << endl;
					cout<<"===========================================\n";
					flowerL=0;
					flowerR=0;
					circleL=0;
					circleR=0;
					squareL=0;
					squareR=0;
					doubleQuo_counter=0;
					singleQuo_counter=0;
					n1=0,n2=0,N1=0,N2=0;
					count_Lines=0;
					SpecialDoubleQuo="\"";
					SpecialSingleQuo="\'";
			
	

			myfile.close();
			return 1;
}

         //check if the the given file directory or not
         //its recurssion function
void checkDir(string dir_path,string en1,vector< unordered_set<string> > &key_word_list)
{
	string path="";
	if(en1=="START")
	{
		path=dir_path;
	}
	else
		path=dir_path+en1;
	DIR *dir;
	struct dirent *en;
	string en2;
	if(path[path.length()-1]!='/')
	{
		path+='/';
	}
	cout<<path<<":dir_path\n";
	const  char* dir_char=path.c_str();
	cout<<dir_char<<":dir_char\n";
	dir=opendir(dir_char);
	cout<<dir<<endl;
	if(dir)
	{
            string file_extension[]={".cpp",".java",".js",".ts",".json",".html",".css"};
			int present=0;
		cout<<"here2\n";
		while((en=readdir(dir))!=NULL)
		{
			present=0;
			en2=en->d_name;
			cout<<":"<<en2<<":";

			if(en2[0]=='.' && (en2.size()==1 || en2.size()==2) )
					continue;
			for(int i = 0;i < (sizeof(file_extension)/sizeof(file_extension[1]));i++)
			{
				
				if( en2.find(file_extension[i]) == (en2.length()-file_extension[i].size() )  && en2.find(file_extension[i]) < en2.length() )
	                {
					 	 cout<<"\ndinesh"<<en2.find(file_extension[i])<<endl;
					 	 cout<<"result"<<en2.length()-file_extension[i].size()<<endl;
			       		 cout<<i<<endl;
							DIR *d_name;
							string inside_path=path+en2;
							const  char* dir_c=inside_path.c_str();
							d_name=opendir(dir_c);
							if(d_name)
							{

								checkDir(path,en2,key_word_list);
								present++;
							}
							else
							{
                                checkValuesOfThefile(path,en2,key_word_list[i]);
								present++;
							}	 
		                 break;
		            }

	        }
		
			//	cout<<"here"<<endl;
			if(present==0)
				checkDir(path,en2,key_word_list);
		}
		closedir(dir);
	}
	cout<<path<<"is not a directory\n";
}

int  LoadKeywordFile(string filePath,vector<unordered_set <string> >& key_word_list)
{
	ifstream operators_list;
	operators_list.open(filePath,ios::in);
	unordered_set<string> keyword;

	string key;
	if(operators_list.is_open())
	{
		cout<<"keyword file is opened\n";
		while(!operators_list.eof())
		{
			getline(operators_list,key,' ');//delimiter space
			keyword.insert(key);
	 	}
		key_word_list.push_back(keyword);
	}
	else
	{
		cout<<"key word file did't opend"<<endl;
		operators_list.close();
	 	return -1;
	}
	operators_list.close();
	return 1;
}
//outfile and keywords file are loaded here

int main(int argc,char* argv[])
{
	cout<<argc<<"argc\n";
	if(argc==3)
	{
		cout<<"Arguments are provoded !!!!\n";
	}
	else
	{
		cout<<"no arguments";
		return 1;
	}
	char* outfile_path=new char[100];
	cout<<"Enter the output file path with .csv extension :\n";

//	cin.clear();
//	cin.getline(outfile_path,100);

	outfile_path=argv[1];
	cout<<outfile_path<<":outfile\n";

	cout<<outfile_path<<":outfile_path\n";
	outfile.open(outfile_path,ios::trunc);
	if(outfile.is_open())
	{
		cout<<"outfile opened\n";
		// system("Color E4");
		
		outfile<<"file_name"<<","<<"n1"<<","<<"n2"<<","<<"N1"<<","<<"N2"<<","<<"Program_length"<<","<<"Program_vocabulary"<<","<<"Volume"<<","<<"Difficulty"<<","<<"Effort"<<","<<"Estimated_Length"<<","<<"Time_required_to_program(sec)"<<","<<"Number of delivered bugs"<<","<<"cyclometric complexity"<<","<<"Number of lines in the code,"<<"file_path"<<","<<endl;
		//outfile<<"file path"<<","<<"file_name"<<","<<"n1"<<","<<"n2"<<","<<"N1"<<","<<"N2"<<","<<"Program_length"<<","<<"Program_vocabulary"<<","<<"Volume"<<","<<"Difficulty"<<","<<"Effort"<<","<<"Estimated_Length"<<","<<"Time_required_to_program(sec)"<<","<<"Number of delivered bugs"<<","<<"Number of lines in the code"<<","<<"cyclometric complexity"<<","<<endl;
	}
	else
	{
		cout<<"outfile not found\n";
		return 1;
	}
	string paths[]={ "./key_words_cpp.txt","./key_words_java.txt","./key_words_js.txt","./key_words_ts.txt","./key_words_json.txt","./key_words_html.txt","./key_words_css.txt" };
	vector< unordered_set<string> > key_word_list;

	for(string path : paths )
	{
		if(LoadKeywordFile(path,key_word_list) == -1)
		{
			return 1;
			break;
		}
	}
	checkDir(argv[2],"START",key_word_list);
	outfile<<"Total Lines of the Project "<<",,,,,,,,,,,,,,"<<TotalCount<<endl;
	outfile<<"\033[1;31mbold red text\033[0m\n";
	outfile.close();//close the outfile;
	cout << "\033[1;31mbold red text\033[0m\n";
	return 0;
}