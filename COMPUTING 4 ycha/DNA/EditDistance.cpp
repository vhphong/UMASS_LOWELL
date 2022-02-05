/***********************************************************************************/
/* EditDistance.cpp                                                                */
/* Yoo Min Cha          								      */
/* DNA Sequence Alignment                                                          */
/* Professor Martin			          						*/
/* 14 February 2014 						            			*/
/***********************************************************************************/

#include "EditDistance.hpp"

using namespace std;

EditDistance::EditDistance(string a, string b):
X(a.begin(), a.end()), Y(b.begin(), b.end()), 
CostMatrix(a.size()+1, vector<int> (b.size()+1, 0))
{
}

void EditDistance::printMatrix() const
{
   for (int i = 0; i < CostMatrix.size(); i++)
   {
	  for (int j = 0; j < CostMatrix[i].size(); j++)
		 cout << CostMatrix[i][j] << ' ';
	  cout << endl;
   }
}

int EditDistance::penalty(char a, char b)
{
   return (a == b ? 0 : 1);
}

int EditDistance::min(int a, int b, int c)
{
   if (a < b && a < c)
	  return a;
   else if (b < c)
	  return b;
   else
	  return c;
}

string EditDistance::Alignment()
{
    string output = "";
    int i(0), j(0);
    
    while ((i!=Y.size()) || (j!=X.size()))
	{	    
        if ((i<Y.size()) && (CostMatrix[j][i] - CostMatrix[j][i+1] == 2))
		{
            output = output + '-' + ' ' + Y[i] + ' ' + '2' + '\n';
            i++;
        } 
        else if ((j<X.size()) && (CostMatrix[j][i] - CostMatrix[j+1][i] == 2))
		{
            output = output + X[j] + ' ' + '-' + ' ' + '2' + '\n';
            j++;
        } 
        else 
		{
			output = output + X[j] + ' ' + Y[i] + ' ' + char('0'+penalty(X[j],Y[i])) + '\n';
			i++;
			j++;
        }
	}
	return output;
}

   // populate matrix and return the optimal distance
int EditDistance::OptDistance()
{
   for (int i = X.size()-1; i >= 0; i--)
	  CostMatrix[i][Y.size()] = CostMatrix[i+1][Y.size()]+2;
   for (int i = Y.size()-1; i >= 0; i--)
	  CostMatrix[X.size()][i] = CostMatrix[X.size()][i+1]+2;
   for (int i = Y.size()-1; i >= 0; i--)
   {
	  for (int j = X.size()-1; j >= 0; j--)
	  {
		 int b = penalty(X[j], Y[i]);
		 CostMatrix[j][i] = min((CostMatrix[j+1][i+1]+b),(CostMatrix[j+1][i]+2),(CostMatrix[j][i+1]+2));
	  }
   }
   return CostMatrix[0][0];
}

int EditDistance::getXsize() const
{
   return X.size();
}

int EditDistance::getYsize() const
{
   return Y.size();
}

char EditDistance::getX(int i) const
{
   return X[i];
}

char EditDistance::getY(int i) const
{
   return Y[i];
}
