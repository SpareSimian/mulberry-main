/*
    Copyright (c) 2007 Cyrus Daboo. All rights reserved.
    
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <iostream.h>
#include <string>
#include <fstream.h>

using namespace std;

void doIcon(const string& resid, const string& filename );

int main()
{
  string resid, filename, restype, discardable;
  cout << "#include <JXPM.h>" << endl;

  cin >> resid >> restype >> discardable >> filename;
  while (!cin.eof()) {
    if (restype == "ICON") {
      doIcon(resid, filename);
    } else {
      cerr << "Unknown restype (" << restype << " for Resource " << resid << endl;
    }
    cin >> resid >> restype >> discardable >> filename;
  }
}

void doIcon(const string& resid, const string& filename )
{
  ifstream xpmfile(filename.c_str());
  if (!xpmfile.good()) {
    cerr << "Couldn't open " <<'"'<< filename <<'"'<< endl;
    return;
  }
  string iconname =  resid.substr(2, resid.length() - 2);
  cout << "AddGlobalResource(" << resid << ", " << iconname << ");" << endl;
}
