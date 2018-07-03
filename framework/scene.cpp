#include "scene.hpp"
#include <vector>
using namespace std;
/*string open_sdf_datei(string const& filename){
	ifstream inf;
	inf.open(filename);
	string sline;
	string s="111";
	 vector<string> text(1000);

	string differ_string;

	if(!inf){
		cerr<<"open failed"<<endl;
	}
	while(getline(inf,sline)){
		istringstream sin(sline);
		while(sline>>differ_string){
			if(differ_string=="define"){
				sline>>differ_string;
				if(differ_string=="material"){
					sline>>differ_string
				}
			}

		}
	}
	while(getline(inf,sline)){
		istringstream istrm(sline);
		while(istrm>>differ_string){
			text.push_back(differ_string);
		}
	}
	inf.close();
	std::vector<string>::iterator it=text.begin();
	while(  it !=text.end()){
		cout<<*(it)<<endl;
		++it;
	}
	return s;
}*/
void open_sdf_datei(string const& filename){
  ifstream inf;
  inf.open(filename);
  string sline;
  vector<string> text;
  
  Material c;
  string name=c.name;
  float ka_r=(c.ka).r;
  float ka_g=(c.kd).g;
  float ka_b=(c.ka).b;

  float kd_r=(c.kd).r;
  float kd_g=(c.kd).g;
  float kd_b=(c.kd).b;

  float ks_r=(c.ks).r;
  float ks_g=(c.ks).g;
  float ks_b=(c.ks).b;

  float material_m = c.exponente_m;

  string differ_string;
  if(!inf){
    cerr<<"open failed"<<endl;
  }
  while(getline(inf,sline)){
    istringstream istrm(sline);
    while(istrm>>differ_string){
      if(differ_string=="#")
           {
            break;
        }
        if(differ_string=="define"){
             //text.push_back(differ_string);
             cout<<"define";
             istrm>>differ_string;
             if(differ_string=="material"){
              cout<<" material"<<endl;
              istrm>>name;
              cout<<name<<" ";

              istrm>>ka_r;
              istrm>>ka_g;
              istrm>>ka_b;
              cout<<ka_r<<" "<<ka_g<<" "<<ka_b<<" ";

              istrm>>kd_r;
              istrm>>kd_g;
              istrm>>kd_b;
              cout<<kd_r<<" "<<kd_g<<" "<<kd_b<<" ";

              istrm>>ks_r;
              istrm>>ks_g;
              istrm>>ks_b;
              cout<<ks_r<<" "<<ks_g<<" "<<ks_b<<" ";

              istrm>>material_m;
              cout<<material_m<<endl;

             }
             if(differ_string=="shape"){
              cout<<" shape"<<endl;
             }
             if(differ_string=="light"){
              cout<<" light"<<endl;
             }
             if(differ_string=="camera"){
              cout<<" camera"<<endl;
             }
        }
        if(differ_string=="render"){
          cout<<"render"<<endl;
        }
      }
    }
  /*
  while(getline(inf,sline)){
    istringstream istrm(sline);
    while(istrm>>differ_string){
      text.push_back(differ_string);
    }
  }*/
  /*inf.close();
  std::vector<string>::iterator it=text.begin();
  while(  it !=text.end()){
    cout<<*(it)<<endl;
    ++it;
  }*/

}