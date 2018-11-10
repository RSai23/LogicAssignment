#include<iostream>
#include<cstring>
using namespace std;
//done by R.Sairam and Tanishk Agarwal
/**
\fn the function returns that position of a string wherein there is an operator and the number of open and
closed brackets are equal before it.In this count the first and last brackets are excluded.
*/
int has_equal_brackets(string a)
{
    int x=0,y=0;
    for(int i=1;i<a.length()-1;i++)
    {
        if(a[i]=='(')x++;
        if(a[i]==')')y++;
        if(a[i]=='^'||a[i]=='V'||a[i]=='>')
        {
            if(x==y)return i;
            else continue;
        }

    }
}
/**
\fn all the proof rules have been checked in this function.
*/

int main()
{
    int valid=1;//valid=1,=>valid else invalid
    int n;
    scanf("%d",&n);
    string arr[n];
    string rule;
    /*input should be perfectly parenthesized i.e input should be given as (a^b) and not a^b*/
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    for(int i=0;i<n;i++)
    {

        string rule=arr[i].substr(arr[i].find('/')+1);
        arr[i].erase(arr[i].find('/'));//shortened array
        if(rule[0]=='P')continue;//assuming that premise is syntactically valid
        else if(rule[0]=='^')//and
        {
            if(rule[1]=='i')//and introduction
            {
                string temp1, temp2;
    	        string str1= rule.substr(rule.find('/')+1);
    	        string str2= str1.substr(str1.find('/')+1);
    	        int line1=stoi(str1);
    	        int line2=stoi(str2);
    	        temp1.append("(");
    	        temp1.append(arr[line1-1]);
    	        temp1.append("^");
    	        temp1.append(arr[line2-1]);
    	        temp1.append(")");
    	        temp2.append("(");
    	        temp2.append(arr[line2-1]);
    	        temp2.append("^");
    	        temp2.append(arr[line1-1]);
    	        temp2.append(")");
    	        if(!(arr[i].compare(temp1))){if(arr[i].compare(temp2))valid=1;}
    	        else
    	        {cout<<"invalid proof";break;}
    	    }


            else//and elimination
            {
                if(rule[2]=='1')//^e1
                {
                    int line=stoi(rule.substr(rule.find('/')+1));
                    string temp=arr[line-1].substr(1,has_equal_brackets(arr[line-1])-1);
                    if(!arr[i].compare(temp))valid=1;
                    else{cout<<"invalid";break;}

                }
                else if (rule[2]=='2')//^e2
                {
                    int line=stoi(rule.substr(rule.find('/')+1));
                    string temp=arr[line-1].substr(has_equal_brackets(arr[line-1])+1,arr[i].length());
                    if(!arr[i].compare(temp))valid=1;
                    else{cout<<"invalid";break;}
                }
                else{cout<<"invalid proof";break;}
            }
        }
        else if(rule[0]=='V')//or introduction
        {

            if(rule[2]=='1')//Vi1
            {
               int line=stoi(rule.substr(rule.find('/')+1));
               string temp = arr[i].substr(1,has_equal_brackets(arr[i])-1);
               if(!arr[line-1].compare(temp))valid=1;
               else{cout<<"invalid";break;}
            }
            else if(rule[2]=='2')//Vi2
            {
                int line=stoi(rule.substr(rule.find('/')+1));
    	        string temp = arr[i].substr(has_equal_brackets(arr[i])+1,arr[line-1].length());
    	        if(!arr[line-1].compare(temp))valid=1;
                else{cout<<"invalid";break;}
            }
            else{cout<<"invalid proof";break;}
        }
        else if(rule[0]=='>')//implication elimination
        {

    	        string str1= rule.substr(rule.find('/')+1);
    	        string str2= str1.substr(str1.find('/')+1);
    	        int line1=stoi(str1);
    	        int line2=stoi(str2);
    	        if(arr[line1-1].length()>arr[line2-1].length())
                {
                    string temp1=arr[line1-1].substr(1,has_equal_brackets(arr[line1-1])-1);
                    string temp2=arr[line1-1].substr(has_equal_brackets(arr[line1-1])+1,arr[i].length());
                    if(!arr[line2-1].compare(temp1)){if(!arr[i].compare(temp2))valid=1;}
                    else
                    {
                        cout<<"invalid proof";break;
                    }
                }
                else if(arr[line2-1].length()>arr[line1-1].length())
                {
                    string temp1 = arr[line2-1].substr(1,has_equal_brackets(arr[line2-1])-1);
                    string temp2 = arr[line2-1].substr(has_equal_brackets(arr[line2-1])+1,arr[i].length());
                    if(!arr[line1-1].compare(temp1)){if(!arr[i].compare(temp2))valid=1;}
                    else
                    {
                        cout<<"invalid proof";break;
                    }
                }


        }
        else if(rule[0]=='M')//Modus Tollens
        {
                string str1= rule.substr(rule.find('/')+1);
    	        string str2= str1.substr(str1.find('/')+1);
    	        int line1=stoi(str1);
    	        int line2=stoi(str2);
    	        if(arr[line1-1].length()>arr[line2-1].length())
                {
                    string temp1="~"+arr[line1-1].substr(1,has_equal_brackets(arr[line1-1])-1);
                    string temp2="~"+arr[line2-1].substr(has_equal_brackets(arr[line2-1])+1,arr[i].length());
                    if(!arr[line2-1].compare(temp2)){if(!arr[i].compare(temp1))valid=1;}
                    else
                    {
                        cout<<"invalid proof";break;
                    }

                }
                 else if(arr[line2-1].length()>arr[line1-1].length())
                 {
                     string temp1="~"+arr[line2-1].substr(1,has_equal_brackets(arr[line2-1])-1);
                     string temp2="~"+arr[line1-1].substr(has_equal_brackets(arr[line1-1])+1,arr[i].length());
                     if(!arr[line1-1].compare(temp2)){if(!arr[i].compare(temp1))valid=1;}
                     else
                    {
                        cout<<"invalid proof";break;
                    }

                 }

        }

    }



    if(valid==1)
    {
        cout<<"valid proof";
    }

return 0;

}

