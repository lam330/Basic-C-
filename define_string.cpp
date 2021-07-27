#pragma warning(disable : 4996)
#include <iostream>
using namespace std;

class MyString
{
private:
	char* str;
	int len;
public:
	MyString()
	{
		len = 0;
		str = new char[1];
		str[0] = '\0';
	}
	MyString(const int& length)// empty rong
	{
		len = length;
		str = new char[length];
		str[len - 1] = '\0';
	}
	MyString(const char* source)
	{
		if (source!=NULL)//k null, s co ms ms copy
		{
			len = strlen(source) + 1;// strlen k tinh '\0'
			str = new char[len];
			Set0();
			strcpy(str, source);
			str[len - 1] ='\0';

		}
		else
		{
			len = 0;
			str = new char[1];
			str[0] = '\0';
			//*this = MyString();
		}
	} //
	MyString(const MyString& source)
	{
		len = source.len+1;
		str = new char[len];
		Set0();
		if (source.str!=NULL)
		{
			strcpy(str, source.str);
			str[len - 1] = '\0';
		}
		else
		{
			len = 0;
			str = new char[1];
			str[0] = '\0';
		}
	}
	~MyString()
	{
		if (str!=NULL)// k null
		{
			delete[] str;
			str = NULL;
			len = 0;
		}
	}

	int GetLength()
	{
		return len;
	}

	char* GetStr()
	{
		return str;
	}

	void Set0()
	{
		for (int i = 0; i < len; i++)// avoid getting trash value 
		{
			str[i] = '\0';
		}
	}
	//combo gan
	MyString& operator=(const MyString& rhs)// gan doi tuong
	{
		if (this == &rhs)
		{
			return *this;
		}
		delete[] str;
		str = NULL;
		str = new char[strlen(rhs.str) + 1];
		strcpy(str, rhs.str);

		return *this;
	}
	MyString& operator=(const char* s)
	{
		if (str == s)
		{
			return *this;
		}
		delete[] str;
		str = NULL;
		str = new char[strlen(s) + 1];
		strcpy(str, s);

		return *this;
	}
	//combo nhap xuat
	friend ostream& operator<<(ostream& output, const MyString& obj)
	{
		output << obj.str;
		return output;
	}        
	friend istream& operator>>(istream& input, MyString& obj)
	{
		char* buff = new char[1000];
		input >> buff;
		obj = MyString{ buff };// ???

		delete[] buff;
		buff = NULL;
		return input;
	}
	// +
	friend MyString operator+(const MyString& lhs, const MyString& rhs)
	{
		int newLength = strlen(lhs.str) + strlen(rhs.str);
		char* buff = new char[newLength + 2];
		strcpy(buff, lhs.str);
		strcat(buff, " ");
		strcat(buff, rhs.str);

		MyString temp{ buff };
		delete[] buff;
		buff = NULL;

		return temp;
	}

	//method: dao, xoa, chen
	void Reverse(const MyString& obj)
	 {
		//MyString temp;
		len = strlen(obj.str)+1;
		str = new char[len];
		
		for (size_t i = 0; i < strlen(obj.str); i++)//size_t, strlen() > kdl cua int=
		{
			str[i] = obj.str[(strlen(obj.str) - 1) - i];
		}
		str[len - 1] = '\0';
		
	 }

	
	MyString& Delete(const int &beginPoint, const int &endPoint)
	{
		MyString temp;
		
		temp.len = strlen(str) - (endPoint - beginPoint + 1);
		
		temp.str = new char[temp.len + 1];
		// 2 index rieng cho 2 mang
		int j = 0;
		for ( int i = 0; i <  strlen(str); i++)
		{
			
			if ((i < beginPoint) || (i > endPoint))
			{
				temp.str[j] = str[i];
				j++;
			}
			
		}
		temp.str[temp.len] = '\0';
	

		return *this = temp;

	}
	// Insert 
	void insert(const int& pos, const MyString& obj)
	{
		
		MyString temp1;// obj contains elements before pos
		temp1.len = pos+1;
		temp1.str = new char[temp1.len + 1];
		temp1.Set0();
		
		for (int i = 0; i < temp1.len; i++)
		{
			temp1.str[i] = str[i];
		}
		temp1.str[temp1.len] = '\0';

		MyString temp2;// obj contains elements after pos
		temp2.len = strlen(str) - strlen(temp1.str)+1;
		temp2.str = new char[temp2.len + 1];
		temp2.Set0();
		int j = 0;
		for (int i = pos ; i < strlen(str); i++)
		{
			temp2.str[j] = str[i];
			j++;
		}
		temp2.str[temp2.len] = '\0';

		strcpy(str, temp1.str);
		strcat(str, " ");
		strcat(str, obj.str);
		strcat(str, " ");
		strcat(str, temp2.str);

	}
	//combo so sanh
	bool operator>(const MyString& obj)
	{
		if (strlen(str) > strlen(obj.str))
		{
			return true;
		}
		return false;
	}
	bool operator<(const MyString& obj)
	{
		if (strlen(str) < strlen(obj.str))
		{
			return true;
		}
		return false;
	}
	bool operator==(const MyString& obj)
	{
		if (strlen(str) == strlen(obj.str))
		{
			return true;
		}
		return false;
	}

};

int main()
{
	MyString a("Hello");
	cout << "String a: " << a<<endl;
	MyString b("World!");
	cout << "String b: " << b<<endl;
	MyString c(b);
	cout << "String c: " << b<<endl;

	MyString d;
	d = a + b;
	cout << "String d: " << d<<endl;

	MyString e;
	e.Reverse(d);
	cout << "String e: " << e << endl;

	MyString f(e);
	f.Delete (5,8);
	cout << "String f: " << f<<endl;
	
	MyString g(a);
	//g.insert(2, "lam");
	cout << "string g: " << g << endl;
	return 0;
}


