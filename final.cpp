#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <map>
#include <algorithm> 

using namespace std;


struct node
{
		int nodeid;
		vector<float> left;
		vector<float> right;
};
struct  point
{
	int x;
	int y;
};
struct bumppoint
{
		vector<point> bumppoints;
};
int main(int argc,char* argv[])
{
	freopen(argv[2],"w",stdout);

	fstream testfile;
	int width;
	int spacing;
	float bound[4]={0};
	int dri,bum;
	int i,j;
	int count;
	int head,tail;
	int tail1;
 	testfile.open(argv[1],ios::in);//file open
	
    string buffer;
	string temp;  
	string cut;
	string t;
	getline(testfile,buffer,'E');//read file
    
	///////get designboundary
	head = buffer.find(' ');
	tail = buffer.find_first_of('\n');
	tail = tail - head ;

    temp = buffer.substr(head+1,tail);
	for( i = 0 ; i<4 ; i++)
    {
    tail1 = temp.find(' ');
    t =  temp.substr(0,tail1);
    bound[i] = atoi(t.c_str());
    //cout << "t:" << t << endl;
    temp = temp.substr(tail1+1);
    //cout << "bound:" <<  bound[i] << endl;
    }
    cout << "designboundary:" ;
	for( i = 0 ; i<4 ; i++) 
	{ cout << bound[i] << " " ;}
    cout << endl;


    /////////get width
	head = buffer.find('w');
	buffer = buffer.substr(head);
	//cout << buffer << endl;
	head = buffer.find(' ');
	tail = buffer.find_first_of('\n');
	tail = tail - head;
	//cout << "head:" << head << "tail:" << tail << endl;
	width = atoi( buffer.substr(head+1,tail).c_str());
    cout << "width:" << width << endl;

    ////////get spacing
	head = buffer.find('s');
	buffer = buffer.substr(head);
	head = buffer.find(' ');
	tail = buffer.find_first_of('\n') - head ;
	spacing = atoi ( buffer.substr(head+1,tail).c_str());
	cout << "spacing:" << spacing << endl;


    ///////get driver
    head = buffer.find('d');
	buffer = buffer.substr(head);
	head = buffer.find(' ');
	tail = buffer.find_first_of('\n') ;
	temp = buffer.substr(tail+1);
	tail = tail - head;
    dri = atoi ( buffer.substr(head+1,tail).c_str());
	cout << "driver:" << dri << endl;
	buffer = temp ;
	////declare driver
	vector<vector<float> > driver(dri,vector<float>(5));
    //cout << buffer << endl;
    for(i=0 ; i < dri ; i++)
    {
		for(j = 0; j<5 ;j++)
			{
				if(j==0)
			    {
					driver[i][j] = atoi(buffer.substr(4*j,4*j+3).c_str());
					}
				else
				{
					driver[i][j] = atoi(buffer.substr(4*j,4*j+3).c_str());
					}
			    cout << setw(4) << driver[i][j] ;
    		}
		cout << endl;
		buffer = buffer.substr(21);
	}	
	
    //cout << buffer << endl;
	
	///////get bump
	head = buffer.find(' ');
	tail = buffer.find_first_of('\n') ;
	temp = buffer.substr(tail+1);
	tail = tail - head;
	bum = atoi ( buffer.substr(head+1,tail).c_str());
	cout << "bump:" << bum << endl;
	buffer = temp;
	////declare bump
	vector<vector<float> > bump(bum,vector<float>(5));
    for(i=0 ; i < bum ; i++)
    {
		for(j = 0; j<5 ;j++)
			{
				if(j==0)
			    {
					bump[i][j] = atoi(buffer.substr(4*j,4*j+3).c_str());
					}
				else
				{
					bump[i][j] = atoi(buffer.substr(4*j,4*j+3).c_str());
					}
			    cout << setw(4) << bump[i][j] ;
    		}
		buffer = buffer.substr(21);
		cout << endl;
    }



	/////////spilt_driver
	int dri_spilt[dri];
	float slope_up;
	float slope_down;
	slope_down = (bound[3] - bound[1])/(bound[2]-bound[0]);
	slope_up = (bound[1]-bound[3])/ (bound[2]-bound[0]);
	float dri_slope_up;
	float dri_slope_down;


    //cout << slope_up << endl;
	//cout << slope_down << endl;

	for(i = 0 ; i < dri ; i++)
		{
			dri_slope_down = (driver[i][4] - bound[1])/(driver[i][3] - bound[0]);	
			dri_slope_up = (bound[1] - driver[i][4] )/ (bound[2] - driver[i][1])  ;

			//cout << driver[i][1] << " " <<driver[i][2] << " " << driver[i][3] << " " << driver[i][4] << endl; 
 

			//cout << "slope_down" << dri_slope_down << endl;
			//cout << "slope_up"<< dri_slope_up << endl;

			if((dri_slope_down >= slope_down) && (dri_slope_up <= slope_up))
			{
					dri_spilt[i] = 1;
			}

			else if ((dri_slope_down <= slope_down) && (dri_slope_up >= slope_up))
			{
					dri_spilt[i] = 2;
			}

			else if ((dri_slope_down >= slope_down) && (dri_slope_up >= slope_up))
			{
					dri_spilt[i] = 3;
			}

			else if ((dri_slope_down <= slope_down)&& (dri_slope_up <= slope_up))
			{
					dri_spilt[i] = 4;
			}


		}


		//for(i = 0; i < dri ; i++)
		//	cout << dri_spilt[i] << endl;


/////////spilt_bump
	int ch[dri] ;
	int bum_spilt[bum];
	float bum_slope_up;
	float bum_slope_down;

	for(i = 0 ; i < bum ; i++)
		{
			bum_slope_down = (bump[i][4] - bound[1])/(bump[i][3] - bound[0]);	
			bum_slope_up = (bound[1] - bump[i][4] )/ (bound[2] - bump[i][1])  ;
			//cout << bump[i1] << " " << bump[i2] << " " << bump[i3] << " " << bump[i4] << endl; 


			//cout << "slope_down" << bum_slope_down << endl;
			//cout << "slope_up"<< bum_slope_up << endl;

			if((bum_slope_down >= slope_down) && (bum_slope_up <= slope_up))
			{
					bum_spilt[i] = 1;
			}

			else if ((bum_slope_down <= slope_down) && (bum_slope_up >= slope_up))
			{
					bum_spilt[i] = 2;
			}

			else if ((bum_slope_down >= slope_down) && (bum_slope_up >= slope_up))
			{
					bum_spilt[i] = 3;
			}

			else if ((bum_slope_down <= slope_down)&& (bum_slope_up <= slope_up))
			{
					bum_spilt[i] = 4;
			}


		}	

		/*for(i = 0; i < bum ; i++)
			cout <<i<<":"<< bum_spilt[i] << endl;*/

/////////check driver and bump iin the same area

	for (i = 0; i < dri; ++i)
	{
		if (dri_spilt[i] == bum_spilt[i])
		{
			ch[i] = 1;
		}

		else ch[i] = 0;
	}

/*	for (i = 0; i < dri; ++i)
	{

		if(ch[i])  cout << "oooooID: "<< i+1 << " 1 " << endl;
		else cout << "xxxxxID: "<< i+1 << " 0 " << endl;


	}
*/


///////// catagory
	map<string ,vector<int> > A;
	map<int ,vector<int> > T;
	vector<int> C;
	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int before;
	count = 1;
/*
	for(i = 0 ; i < bum ; i++) /// push y location into 4 area map
	{
		if(bum_spilt[i] == 1) 
		{
			A["up"].push_back(bump[i][4]) ;/// 
			up++;
		}
		else if(bum_spilt[i] == 2) 
		{
			A["down"].push_back(bump[i][4]);
			down++;
		}
		else if(bum_spilt[i] == 3) 
		{
			A["left"].push_back(bump[i][4]);
			left++;
		}
		else if(bum_spilt[i] == 4) 
		{
			A["right"].push_back(bump[i][4]);
			right++;
		}
	}


	cout << "up:" << A["up"].size() << endl;
	cout << "down:" << A["down"].size() << endl;
	cout << "left:" << A["left"].size() << endl;
	cout << "right:" << A["right"].size() << endl;
	for(i = 0 ; i < A["up"].size() ; i++) cout << "up" << A["up"][i] << endl;
	for(i = 0 ; i < A["down"].size() ; i++) cout << "down" << A["down"][i] << endl;
	for(i = 0 ; i < A["left"].size() ; i++) cout << "left" << A["left"][i] << endl;
	for(i = 0 ; i < A["right"].size() ; i++) cout << "right" << A["right"][i] << endl;
*/
	
	//cout<<"bump:"<<driver[13][1]<<" "<<driver[13][2]<<" "<<driver[13][3]<<" "<<driver[13][4]<<endl;
////////////////////////for section 1/////////////////////////////
		C.push_back(bump[0][4]);
	for (i = 0 ; i < bum ; i++)
	{
		if(i > 0)
		{
			if(bump[i][4]!=before) 
			{
				C.push_back(bump[i][4]);
				count++;
			//	cout<<"before:"<<before<<endl;
			}
		}
		T[bump[i][4]].push_back(bump[i][0]);//for every differnt y number
		before  = bump[i][4];
		//cout << "i number:"<< i << endl;
	}
	//cout << "y number:"<< count << endl;

	sort(C.begin(),C.end());//sort the y value small---->big
	/*for(i=0;i<C.size();i++)
		{
			cout << "<------y:"<< C[i] << endl;
			for(j = 0 ; j < T[C[i]].size() ; j++)
				cout << T[C[i]][j] << endl;
		}*/
	
 	vector<vector<float> > bumplist(bum+1,vector<float>(5)); 
	for(i=0;i<bum;i++)
	{
		bumplist[bump[i][0]] [0]=bump[i][1];
		bumplist[bump[i][0]] [1]=bump[i][2];
		bumplist[bump[i][0]] [2]=bump[i][3];
		bumplist[bump[i][0]] [3]=bump[i][4];
		
	}

	vector<node> nodelist(bum+1) ;

	
	for (int l = 0; l < T.size()-1; l++)//total line
	{
		
		

		for(j = 0 ; j < T[C[l]].size() ; j++)//now line
		{


				//cout << T[C[0]][j] << endl;
														//C[] differnt y location
				for(int k = 0 ; k<T[C[l+1]].size();k++)  //T[C[0]] the first line T[C[1]]: the second line  //k=nextline 
				{		//cout<<"taget "<< T[C[l+1]][k]<<" now:"<<T[C[l]][j]<<endl;
					if(  driver[T[C[l]][j]-1][0]< driver[ T[C[l+1]][k]-1 ][0]){
					
						nodelist[T[C[l+1]][k]].left.push_back(T[C[l]][j])  ;//push into T[C[i]][k]'s left 
					
					break;
					}
					else if(k==T[C[l+1]].size()-1){
					nodelist[T[C[l+1]][k]].right.push_back(T[C[l]][j]);
					//cout<<"taget "<< driver[ T[C[l+1]][k]-1 ][0]<<" now:"<<driver[T[C[l]][j]-1][0]<<endl;
					}

				}
			
			for(int z=0 ;z<nodelist[T[C[l]][j]].right.size();z++){

					for(int k = 0 ; k<T[C[l+1]].size();k++)  //T[C[0]] the first line T[C[1]]: the second line
				{		//cout<<"taget "<< T[C[l+1]][k]<<" now:"<<T[C[l]][j]<<endl;
					if(  driver[nodelist[T[C[l]][j]].right[z]-1][0]< driver[ T[C[l+1]][k]-1 ][0]){
					
						nodelist[T[C[l+1]][k]].left.push_back(nodelist[T[C[l]][j]].right[z])  ;//push into T[C[i]][k]'s left 
					
					break;
					}
					else if(k==T[C[l+1]].size()-1){
					nodelist[T[C[l+1]][k]].right.push_back(nodelist[T[C[l]][j]].right[z]);
					//cout<<"taget "<< driver[ T[C[l+1]][k]-1 ][0]<<" now:"<<driver[T[C[l]][j]-1][0]<<endl;
					}

				}
			}
			for(int z=0 ;z<nodelist[T[C[l]][j]].left.size();z++){

					for(int k = 0 ; k<T[C[l+1]].size();k++)  //T[C[0]] the first line T[C[1]]: the second line
				{		//cout<<"taget "<< T[C[l+1]][k]<<" now:"<<T[C[l]][j]<<endl;
					if(  driver[nodelist[T[C[l]][j]].left[z]-1][0]< driver[ T[C[l+1]][k]-1 ][0]){
					
						nodelist[T[C[l+1]][k]].left.push_back(nodelist[T[C[l]][j]].left[z])  ;//push into T[C[i]][k]'s left 
					
					break;
					}
					else if(k==T[C[l+1]].size()-1){
					nodelist[T[C[l+1]][k]].right.push_back(nodelist[T[C[l]][j]].left[z]);
					//cout<<"taget "<< driver[ T[C[l+1]][k]-1 ][0]<<" now:"<<driver[T[C[l]][j]-1][0]<<endl;
					}

				}
			}



		}
	}


		for(i=1;i<=bum;i++)
		{
			sort(nodelist[i].left.begin(),nodelist[i].left.end());
			sort(nodelist[i].right.begin(),nodelist[i].right.end());
		}

/*
		for(i=1;i<=bum;i++)
		{
			//cout<<"i:"<<i<<" !"<<"" <<endl;
			for(j=0;j<nodelist[i].left.size();j++)
			{
				cout<<"node:"<<i<<" left"<<nodelist[i].left[j]<<endl;
			}

			for(j=0;j<nodelist[i].right.size();j++)
			{
				cout<<"node:"<<i<<" right"<<nodelist[i].right[j]<<endl;
			}

		}
*/
/*
		
		for(i=0;i<C.size();i++)
		{
			cout << "<------y:"<< C[i] << endl;
			for(j = 0 ; j < T[C[i]].size() ; j++)
				cout << T[C[i]][j] << endl;
		}

*/
		int betweenbumpy=bumplist[T[C[1]][0]][1]-bumplist[T[C[0]][0]][3];//the space between two bump for y
		int betweenbumpx=bumplist[T[C[1]][1]][2]-bumplist[T[C[1]][0]][0];//the space between two bump for x
	//cout<<"x:"<<betweenbumpx<<"y:"<<betweenbumpy<<endl;

		vector<bumppoint> pointlist(bum+1);
		int everyx[bum+1] ;
		for(i=1;i<=bum;i++)
		{
				everyx[i]=(bumplist[i][0]+bumplist[i][2])/2;
			//	cout<<"everyx:" <<everyx[i]<<endl;
		}


		for(int k = 0 ;k<T.size() -1;k++)
	{
		int righty = C[k] + betweenbumpy - spacing- width/2;
		int lefty  =C[k]+spacing+width/2;
	

		//cout<<"x:"<<righty<<"y:"<<lefty<<endl;
		for(j = 0 ; j < T[C[k+1]].size() ; j++){
				//C[1] for the line 9 10 11 12
				
				
				int leftx= bumplist[T[C[k+1]][j]][0]-((nodelist[ T[C[k+1]][j]].left.size()-1)*3+2);
				int rightx= bumplist[T[C[k+1]][j]][2]+2;

			//cout<<"lx:"<<nodelist[ T[C[k+1]][j]].left.size()-1<<"rx"<<rightx<<endl;
			for(i=0;i<nodelist[ T[C[k+1]][j]].left.size();i++){
			//	cout << nodelist[ T[C[1]][j]].left [i]<< endl;
				int  targetnumber= nodelist[ T[C[k+1]][j]].left [i];//now whitch bump in the left
				int bumpnumber= T[C[k+1]][j]; //now whitch bump's left
				point temp1point,temp2point;

				temp1point.x=leftx;
				leftx=leftx-3;
				temp1point.y= bumplist[bumpnumber][3];

				if(everyx[targetnumber]>temp1point.x)
				{	temp2point.x=temp1point.x;
					temp2point.y=lefty;
					lefty=lefty+spacing+width;
				}
				else
				{
					temp2point.x=temp1point.x;
					temp2point.y=righty;
					righty=righty-spacing-width;

				}
					everyx[targetnumber]=temp1point.x;
				//	cout<<"temp1point.x:"<<temp1point.x<<"temp1point.y:"<<temp1point.y<<endl;
				//	cout<<"temp2point.x:"<<temp2point.x<<"temp2point.y:"<<temp2point.y<<endl;
				pointlist[targetnumber].bumppoints.push_back(temp2point);
					pointlist[targetnumber].bumppoints.push_back(temp1point);


			}

		
			for(i=0;i< nodelist[ T[C[k+1]][j]].right.size();i++){
			//	cout << nodelist[ T[C[1]][j]].right [i]<< endl;
				int  targetnumber= nodelist[ T[C[k+1]][j]].right [i];
				int bumpnumber= T[C[k+1]][j];
				point temp1point,temp2point;
				
				temp1point.x=rightx;
				rightx=rightx+3;
				temp1point.y= bumplist[bumpnumber][3];
				
				if(everyx[targetnumber]>temp1point.x)
				{	temp2point.x=temp1point.x;
					temp2point.y=lefty;
					lefty=lefty+spacing+width;
				}
				else
				{
					temp2point.x=temp1point.x;
					temp2point.y=righty;
					righty=righty-spacing-width;

				}
					everyx[targetnumber]=temp1point.x;
					//cout<<"temp1point.x:"<<temp1point.x<<"temp1point.y:"<<temp1point.y<<endl;
					//cout<<"temp2point.x:"<<temp2point.x<<"temp2point.y:"<<temp2point.y<<endl;
				pointlist[targetnumber].bumppoints.push_back(temp2point);
					pointlist[targetnumber].bumppoints.push_back(temp1point);


			}
		}

	}


	int	righty = driver[0][2]-C[C.size()-1]-spacing-width/2;
	int	 lefty  =C[C.size()-1]+spacing+width/2;
			for(int k = 1;k<bum+1;k++)
			{
				point temp1point,temp2point;

				temp1point.y=(driver[k-1][2]+driver[k-1][4])/2;
				temp1point.x=(driver[k-1][1]+driver[k-1][3])/2;
				

				if(everyx[k]>temp1point.x)
				{	temp2point.x=temp1point.x;
					temp2point.y=lefty;
					lefty=lefty+spacing+width;
				}
				else
				{
					temp2point.x=temp1point.x;
					temp2point.y=righty;
					righty=righty-spacing-width;

				}
					everyx[k]=temp1point.x;
					//cout<<"temp1point.x:"<<temp1point.x<<"temp1point.y:"<<temp1point.y<<endl;
					//cout<<"temp2point.x:"<<temp2point.x<<"temp2point.y:"<<temp2point.y<<endl;
					pointlist[k].bumppoints.push_back(temp2point);
					pointlist[k].bumppoints.push_back(temp1point);


			}


/*
		for(i=1;i<bum+1;i++)
		{

			cout<<"for bump:"<<i<<endl;
			for(j=0;j<pointlist[i].bumppoints.size();j++)
				cout<<"x:"<<pointlist[i].bumppoints[j].x<<" y:"<<pointlist[i].bumppoints[j].y<<endl;

		}
*/

			cout<<"net "<<bum<<endl;
		point begin[bum+1];
		for(i=1;i<bum+1;i++)
		{
				cout<<"netid"<<i<<endl;
				begin[i].x =(bumplist[i][0]+bumplist[i][2])/2;
				begin[i].y = (bumplist[i][3]);
				//cout<<begin[i].x<<" "<<begin[i].y<<endl;
				for(j=0;j<pointlist[i].bumppoints.size();j++)
				{

					if((begin[i].y-pointlist[i].bumppoints[j].y)!=0)
					{
						cout<<"wire "<<begin[i].x-width/2<<" "<<begin[i].y<<" "<<begin[i].x+width/2<<" "<<pointlist[i].bumppoints[j].y<<endl;
						begin[i].y=pointlist[i].bumppoints[j].y;

					}
					if(begin[i].x-pointlist[i].bumppoints[j].x!=0)
					{
						cout<<"wire "<<begin[i].x<<" "<<begin[i].y-width/2<<" "<<pointlist[i].bumppoints[j].x<<" "<<pointlist[i].bumppoints[j].y+width/2<<endl;
						begin[i].x=pointlist[i].bumppoints[j].x;
					}

				}

		}
		cout<<"End"<<endl;
return 0;


}