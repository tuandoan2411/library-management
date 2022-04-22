#include<graphics.h>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<ctime>
#include<iostream>
#include<iomanip>
using namespace std;

const int MAX_DS = 1000;

string chuanHoaChuoi( string s ){
    if( s == "" ) return "";
	string result, temp, kq;
	int i = 0;
	while( i < s.length() ){
		while( s[i] != ' ' && i < s.length() ){
			temp += s[i];
			i++;
		}
		while( s[i] == ' ' && i < s.length() ){
			if( temp != "" ){
				result += temp + ' ';
				temp = "";
			}
			i++;
		}
	}
	if( temp != "" ){
		result += temp;
		return result;
	}
	else{
        int b = result.length() - 1;
		for( int i = 0; i < b; i++ ){
			kq += result[i];
		}
		return kq;
	}

}

bool chuoi_toan_so( string s){
	if( s.length() == 0 ) return false;
	for(int i = 0; i < s.length(); i++){
		if( !(s[i] >= '0' && s[i] <= '9') ){
			return false;
		}
	}
	return true;
}

int chuyen_ki_tu_thanh_so(char c){
	if( c == '0' ) return 0;
	else if( c == '1' ) return 1;
	else if( c == '2' ) return 2;
	else if( c == '3' ) return 3;
	else if( c == '4' ) return 4;
	else if( c == '5' ) return 5;
	else if( c == '6' ) return 6;
	else if( c == '7' ) return 7;
	else if( c == '8' ) return 8;
	else if( c == '9' ) return 9;
}

int chuyen_chuoi_thanh_so(string s){
    int result = 0;
    for(int i = 0; i < s.length(); i++){
    	result = result * 10 + 	chuyen_ki_tu_thanh_so(s[i]);
    }
    return result;
}

char chuyen_thanh_ki_tu( int chu_so ){
	if( chu_so == 0 ) return '0';
	if( chu_so == 1 ) return '1';
	if( chu_so == 2 ) return '2';
	if( chu_so == 3 ) return '3';
	if( chu_so == 4 ) return '4';
	if( chu_so == 5 ) return '5';
	if( chu_so == 6 ) return '6';
	if( chu_so == 7 ) return '7';
	if( chu_so == 8 ) return '8';
	if( chu_so == 9 ) return '9';
}

string dao_chuoi( string s){
	for( int i = 0; i < s.length() / 2; i++ ){
		char temp = s[i];
		s[i] = s[s.length() - 1 - i];
		s[s.length() - 1 - i] = temp;
	}
	return s;
}

string chuyen_so_thanh_chuoi(int so){
	string result;
	if(so < 0 ) so *= -1;
	if( so == 0 ) return "0";
	while( so > 0 ){
		int du = so % 10;
		result += chuyen_thanh_ki_tu(du);
		so /= 10;
	}
	result = dao_chuoi(result);
	return result;
}

char* chuyen_string_thanh_char( string a ){
    char* c = new char[a.length() + 1];
    for(int i = 0; i < a.length(); i++ ){
        c[i] = a[i];
    }
    c[a.length()] = '\0';
    return c;
}

struct ControlCell{
    int x;
    int y;
    int width;
    int height;
    int bk_color;
    int color;
    string thong_diep;
    int can_Le;
    int vi_tri;
};

enum {
	QUANLYDG, CAPNHATDG, XEMDG, MUONS, TRAS, SDANGMUON, MUONQUAHAN, THEMDG, XOADG, SUADG,
	MATHETD, HOTENTD, QUANLYDS, CAPNHATDS, XEMDS, TIMS, MUONNHIEUNHAT, THEMDS, XOADS, SUADS
};

void tao_khung(int x, int y, int width, int height, int bk_color, int color, char* thong_diep, int can_le){
    //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setfillstyle(SOLID_FILL, bk_color);
    setcolor(bk_color);
    rectangle(x, y, x + width, y + height);
    int tam_x = (2 * x + width) / 2;
    int tam_y = (2 * y + height) / 2;
    floodfill(tam_x, tam_y, bk_color);
    int t_width = textwidth(thong_diep);
    int t_height = textheight(thong_diep);
    setcolor(color);
    setbkcolor(bk_color);
    if( can_le == -1 ){
        outtextxy(x , tam_y - (t_height / 2), thong_diep);
    }
    else if( can_le == 0 ){
        outtextxy(tam_x - (t_width / 2), tam_y - (t_height / 2), thong_diep);
    }
    else{
        outtextxy(x + width - textwidth(thong_diep), tam_y - (t_height / 2), thong_diep);
    }
    setbkcolor(BLACK);
}

string tao_khung_nhap(int x, int y, int width, int height, int bk_color, int color, int can_le, int max_char, bool (*thoa_dk)(int) ){
    string gach_duoi = "_";
    string input;
    string result;
    int dem = 0;
    while(true){
        cleardevice();
        result = input + gach_duoi;
        tao_khung(x, y, width, height, bk_color, color, chuyen_string_thanh_char(result), can_le);
        char c = getch();
        if( c == 13 ){
            break;
        }
        else if( c == 8 ){
            if( input.length() > 0 ){
                dem--;
                input.erase(input.length() - 1, 1);
            }
        }
        else{
            if( thoa_dk(c) ){
                if( dem < max_char ){
                    dem++;
                    input += " ";
                    input[input.length() - 1] = c;
                }
            }
        }
        delay(10);
    }
    return input;
}

bool da_click_vao(int a, int b, int x, int y, int width, int height){
    return a >= x && a < x + width && b >= y && b < y + height;
}

bool clickControlCell(int x, int y, ControlCell a){
    return x >= a.x && x <= a.x + a.width && y >= a.y && y <= a.y + a.height;
}

void childControlCell(ControlCell a, int ma_tran[20][20], ControlCell* ArrControlCell){
    int start = a.vi_tri;
    for(int i = 0; i < 20; i++ ){
        if(ma_tran[start][i] == 1){
            tao_khung(ArrControlCell[i].x, ArrControlCell[i].y, ArrControlCell[i].width, ArrControlCell[i].height, ArrControlCell[i].bk_color, ArrControlCell[i].color, chuyen_string_thanh_char(ArrControlCell[i].thong_diep), ArrControlCell[i].can_Le);
        }
    }
}

void initArrControlCell(ControlCell* ArrControlCell ){
    //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    int width = textwidth("QUAN LY DAU SACH") + 25;
    int height = textheight("QUAN LY DAU SACH") + 25;
    string mang_thong_diep[20] = {"QUAN LY DOC GIA", "CAP NHAT DOC GIA", "XEM DOC GIA", "MUON SACH",
     "TRA SACH", "SACH DANG MUON", "MUON QUA HAN", "THEM DOC GIA", "XOA DOC GIA", "SUA DOC GIA",
      "MA THE TANG DAN", "HO TEN TANG DAN", "QUAN LY DAU SACH", "CAP NHAT DAU SACH",
       "XEM DAU SACH", "TIM SACH", "MUON NHIEU NHAT", "THEM DAU SACH", "XOA DAU SACH", "SUA DAU SACH"};
    int start_y = 0;
    int start_x = 0;
    int mang_toa_do[20][2] = { {start_x, start_y}, {start_x + width + 3, start_y }, {start_x + width + 3, start_y + height + 3 }, {start_x + width + 3,  start_y + 2 * (height + 3)}, {start_x + width + 3,  start_y + 3 * (height + 3) }, {start_x + width + 3,  start_y + 4 * (height + 3) }, {start_x + width + 3,  start_y + 5 * (height + 3) },
     {start_x + 2 * (width + 3), start_y }, {start_x + 2 * (width + 3), start_y + height + 3 }, {start_x + 2 * (width + 3), start_y + 2 * (height + 3) }, {start_x + 2 * (width + 3), start_y + height + 3 }, {start_x + 2 * (width + 3), start_y + 2 * (height + 3) },
      {start_x , start_y + height + 3 }, {start_x + width + 3, start_y + height + 3 }, {start_x + width + 3,  start_y + 2 * (height + 3) }, {start_x + width + 3,  start_y + 3 * (height + 3) }, {start_x + width + 3,  start_y + 4 * (height + 3) },
       {start_x + 2 * (width + 3), start_y + height + 3 }, {start_x + 2 * (width + 3), start_y + 2 * (height + 3) }, {start_x + 2 * (width + 3), start_y + 3 * (height + 3) } };

    for(int i = 0; i < 20; i++ ){
        ArrControlCell[i].x = mang_toa_do[i][0];
        ArrControlCell[i].y = mang_toa_do[i][1];
        ArrControlCell[i].width = width;
        ArrControlCell[i].height = height;
        ArrControlCell[i].bk_color = RED;
        ArrControlCell[i].color = YELLOW;
        ArrControlCell[i].thong_diep = mang_thong_diep[i];
        ArrControlCell[i].can_Le = 0;
        ArrControlCell[i].vi_tri = i;
    }
}

void initMatran( int ma_tran[20][20] ){
    ifstream ifs("matran.txt", ios::in);
	for(int i = 0; i < 20; i++ ){
	 	for(int j = 0; j < 20; j++ ){
	 		ifs>> ma_tran[i][j];
		}
	}
}

void menu(ControlCell* ArrControlCell){
    tao_khung(ArrControlCell[0].x, ArrControlCell[0].y, ArrControlCell[0].width, ArrControlCell[0].height, ArrControlCell[0].bk_color, ArrControlCell[0].color, chuyen_string_thanh_char(ArrControlCell[0].thong_diep), ArrControlCell[0].can_Le);
    tao_khung(ArrControlCell[12].x, ArrControlCell[12].y, ArrControlCell[12].width, ArrControlCell[12].height, ArrControlCell[12].bk_color, ArrControlCell[12].color, chuyen_string_thanh_char(ArrControlCell[12].thong_diep), ArrControlCell[12].can_Le);
}

bool chi_nhan_chu_cai( int so ){
    return (so >= 'a' && so <= 'z') || (so >= 'A' && so <= 'Z');
}

bool chi_nhan_chu_cai_khoang_trong( int so ){
    return (so >= 'a' && so <= 'z') || (so >= 'A' && so <= 'Z') || so == ' ';
}

bool chi_nhan_chu_cai_so_khoang_trong( int so ){
    return (so >= 'a' && so <= 'z') || (so >= 'A' && so <= 'Z') || (so >= '0' && so <= '9') || so == ' ';
}

bool chi_nhan_chu_cai_so( int so ){
    return (so >= 'a' && so <= 'z') || (so >= 'A' && so <= 'Z') || (so >= '0' && so <= '9');
}


bool chi_nhan_so(int so){
    return so >= '0' && so <= '9';
}

bool chi_nhan_0_1(int so){
    return so == '0' || so == '1';
}

bool nhap_vi_tri_sach(int so){
    return (so >= 'a' && so <= 'z') || (so >= 'A' && so <= 'Z') || (so >= '0' && so <= '9') || so == ' ' || so == ',';
}

const int SODONGHDDOCGIA = 6;
string mang_huong_dan_doc_gia[SODONGHDDOCGIA] = {"HUONG DAN", "MA THE DUOC TAO TU DONG", "HO CHI NHAN CHU CAI, KHOANG TRANG", "TEN CHI NHAN CHU CAI", "PHAI CHI NHAN 1 HOAC 0", "TRANG THAI DUOC KHOI TAO BANG 1"};
const int SODONGHDDAUSACH = 7;
string mang_huong_dan_dau_sach[SODONGHDDAUSACH] = {"HUONG DAN", "ISBN DUOC TAO TU DONG", "TEN SACH CHI NHAN CHU CAI, KHOANG TRANG", "TAC GIA CHI NHAN CHU CAI, KHOANG TRANG", "THE LOAI CHI NHAN CHU CAI, KHOANG TRANG"
, "NAM XUAT BAN CHI NHAN SO", "SO TRANG CHI NHAN SO"};

void gioi_thieu(){
    int so_dong = 6;
    int width = 500;
    int height = 50;
    int x = getmaxx() / 2 - width / 2;
    int y = 200;
    int mang_toa_do[so_dong][2];
    for(int i = 0; i < so_dong; i++){
        mang_toa_do[i][0] = x;
        mang_toa_do[i][1] = y + i * height;
    }
    string mang_thong_diep[so_dong] = {"DE TAI THU VIEN", "HO VA TEN: DOAN TRONG TUAN", "LOP: D18CQCN01-N", "MSSV: N18DCCN196", "FACEBOOK: TUAN DOAN", "EMAIL: doantrongtuan01@gmail.com"};
    for(int i = 0; i < so_dong; i++){
        if( i == 0){
            tao_khung(mang_toa_do[i][0], mang_toa_do[i][1], width, height, RED, YELLOW, chuyen_string_thanh_char(mang_thong_diep[i]), 0);
        }
        else{
            tao_khung(mang_toa_do[i][0], mang_toa_do[i][1], width, height, RED, YELLOW, chuyen_string_thanh_char(mang_thong_diep[i]), 0);
        }
    }
    int width_tiep_tuc = textwidth("TIEP TUC") + 25;
    int height_tiep_tuc = 50;
    int x_tiep_tuc = getmaxx() / 2 - width_tiep_tuc / 2;
    int y_tiep_tuc = mang_toa_do[so_dong - 1][1] + height + 50;
    while(true){
        tao_khung(x_tiep_tuc, y_tiep_tuc, width_tiep_tuc, height_tiep_tuc, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TIEP TUC"), 0);
        delay(100);
        if(ismouseclick(WM_LBUTTONDOWN)){
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if( da_click_vao(x, y, x_tiep_tuc, y_tiep_tuc, width_tiep_tuc, height_tiep_tuc) ){
                cleardevice();
                break;
            }
        }
    }
}

void guide_table_doc_gia(int start_x, int start_y, int width, int height){
    tao_khung(start_x, start_y, width, (height / SODONGHDDOCGIA), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_doc_gia[0]), 0);
    tao_khung(start_x, start_y + (height / SODONGHDDOCGIA), width, (height / SODONGHDDOCGIA), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_doc_gia[1]), 0);
    tao_khung(start_x, start_y + 2 * (height / SODONGHDDOCGIA), width, (height / SODONGHDDOCGIA), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_doc_gia[2]), 0);
    tao_khung(start_x, start_y + 3 * (height / SODONGHDDOCGIA), width, (height / SODONGHDDOCGIA), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_doc_gia[3]), 0);
    tao_khung(start_x, start_y + 4 * (height / SODONGHDDOCGIA), width, (height / SODONGHDDOCGIA), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_doc_gia[4]), 0);
    tao_khung(start_x, start_y + 5 * (height / SODONGHDDOCGIA), width, (height / SODONGHDDOCGIA), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_doc_gia[5]), 0);

}

void guide_table_dau_sach(int start_x, int start_y, int width, int height){
    tao_khung(start_x, start_y, width, (height / SODONGHDDAUSACH), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_dau_sach[0]), 0);
    tao_khung(start_x, start_y + (height / SODONGHDDAUSACH), width, (height / SODONGHDDAUSACH), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_dau_sach[1]), 0);
    tao_khung(start_x, start_y + 2 * (height / SODONGHDDAUSACH), width, (height / SODONGHDDAUSACH), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_dau_sach[2]), 0);
    tao_khung(start_x, start_y + 3 * (height / SODONGHDDAUSACH), width, (height / SODONGHDDAUSACH), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_dau_sach[3]), 0);
    tao_khung(start_x, start_y + 4 * (height / SODONGHDDAUSACH), width, (height / SODONGHDDAUSACH), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_dau_sach[4]), 0);
    tao_khung(start_x, start_y + 5 * (height / SODONGHDDAUSACH), width, (height / SODONGHDDAUSACH), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_dau_sach[5]), 0);
    tao_khung(start_x, start_y + 6 * (height / SODONGHDDAUSACH), width, (height / SODONGHDDAUSACH), LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_huong_dan_dau_sach[6]), 0);

}

class NgayThang{
	int ngay;
	int thang;
	int nam;
	int ngay_max[12];
	public:
		NgayThang( int n = 0, int t = 0, int na = 0 ){
			ngay = n;
			thang = t;
			nam = na;
			for( int i = 0; i < 7; i++ ){
				if( i % 2 == 0) ngay_max[i] = 31;
				else ngay_max[i] = 30;
			}
			for( int i = 7; i < 12; i++ ){
				if( i % 2 != 0) ngay_max[i] = 31;
				else ngay_max[i] = 30;
			}
			if( nam % 4 == 0 && nam % 100 != 0 ){
				ngay_max[1] = 29;
			}
			else ngay_max[1] = 28;
		}

		int get_ngay(){
			return ngay;
		}

		int get_thang(){
			return thang;
		}

		int get_nam(){
			return nam;
		}

		int get_ngay_max( int i){
			return ngay_max[i];
		}

		int set_ngay( int n ){
			ngay = n;
		}

		int set_thang( int n ){
			thang = n;
		}

		int set_nam( int n ){
			nam = n;
		}

		NgayThang ngay_sau(){
			NgayThang moi( ngay + 1, thang, nam );
			if( moi.get_ngay() > moi.ngay_max[thang - 1] ){
					moi.set_ngay( 1 );
					moi.set_thang( moi.get_thang() + 1 );
					if( moi.get_thang() > 12 ){
						moi.set_ngay( 1 );
						moi.set_thang( 1 );
						moi.set_nam( moi.get_nam() + 1 );
					}
			}
			return moi;
		}

		bool ngay_hop_le(){
            time_t baygio = time(0);
            tm *ltm = localtime(&baygio);
            int nam_hien_tai = 1900 + ltm->tm_year;
            return 1 <= nam && nam <= nam_hien_tai && 1 <= thang && thang <= 12 && 1 <= ngay && ngay <= ngay_max[thang - 1];
        }

		NgayThang ngay_truoc(){
			NgayThang moi( ngay - 1, thang, nam );
			if( moi.get_ngay() == 0 ){
					moi.set_ngay( moi.ngay_max[moi.get_thang() - 2] );
					moi.set_thang( moi.get_thang() - 1 );
					if( moi.get_thang() == 0 ){
						moi.set_ngay( ngay_max[11] );
						moi.set_thang( 12 );
						moi.set_nam( moi.get_nam() - 1 );
					}
			}
			return moi;
		}

		int kc_giua_2_ngay( NgayThang ngay_truoc){
			int result = 0;
			for(int i = ngay_truoc.get_nam(); i < nam; i++ ){
				if( i % 4 == 0 && i % 100 != 0) result += 366;
				else result += 365;
			}

			for( int i = 0; i < ngay_truoc.get_thang() - 1; i++ ){
				result -= ngay_truoc.get_ngay_max(i);
			}
			result -= ngay_truoc.get_ngay();

			for( int i = 0; i < thang - 1; i++ ){
				result += ngay_max[i];
			}
			result += ngay;
			return result;
		}
};

template <class T>
class MangMotChieu{
	int n;
	T* a;
	public:
		MangMotChieu(){
			n = 0;
			a = NULL;
		}

		int size(){
			return n;
		}

		void resize( int moi ){
			if( a == NULL ){
				a = new T[moi];
			}
			else{
				// cap vung nho moi
				T* temp = new T[moi];
				// sao chep vung nho cu vao vung nho moi
				int nho_hon;
				if( moi > n ) nho_hon = n;
				else nho_hon = moi;
				for( int i = 0; i < nho_hon; i++ ){
					temp[i] = a[i];
				}
				// xoa vung nho cu
				delete[] a;
				// gan a toi vung nho moi
				a = temp;
			}
			n = moi;
		}

		T& operator[]( int i ){
			return a[i];
		}

		void push_back( T gia_tri ){
			resize( n + 1 );
			a[n - 1] = gia_tri;
		}

		T pop_back(){
			T temp = a[n - 1];
			resize( n - 1 );
			return temp;
		}

		void insert( int pos, T gia_tri ){
			resize( n + 1 );
			for( int i = n - 1; i > pos; i-- ){
				a[i] = a[i - 1];
			}
			a[pos] = gia_tri;
		}

		void xoa_vi_tri( int pos ){
			for( int i = pos; i < n - 1; i++ ){
				a[i] = a[i + 1];
			}
			resize( n - 1);
		}

		void sap_xep( bool (*cmp)(T, T)){
			for( int i = 0; i < n - 1; i++ ){
				for( int j = 0; j < n - 1 - i; j++){
					if( !cmp( a[j], a[j + 1] ) ){
						T temp = a[j];
						a[j] = a[j + 1];
						a[j + 1] = temp;
					}
				}
			}
		}
};

template <class T>
class Nut{
	T data;
	Nut<T>* next;
	public:
		Nut( T gia_tri ){
			data = gia_tri;
			next = NULL;
		}

		void set_next( Nut<T>* a ){
			next = a;
		}

		void set_data( T a ){
			data = a;
		}

		Nut<T>* get_next(){
			return next;
		}
		T& get_data(){
			return data;
		}
};

template <class T>
class LienKetDon{
	Nut<T>* head;
	public:
		LienKetDon(){
			head = NULL;
		}

		Nut<T>* get_head(){
			return head;
		}

		void addFirst( T gia_tri ){
			Nut<T>* newnode = new Nut<T>(gia_tri);
			newnode->set_next( head );
			head = newnode;
		}

		void addEnd( T gia_tri ){
			Nut<T>* newnode = new Nut<T>(gia_tri);
			Nut<T>* temp = head;
			if( temp == NULL ){
				head = newnode;
				return;
			}
			while( temp->get_next() != NULL ) temp = temp->get_next();
			temp->set_next( newnode );

		}

		T deleteFirst(){
			if( head ){
				T result = head->get_data();
				Nut<T>* temp = head;
				head = head->get_next();
				delete temp;
				return result;
			}
		}

		void in_du_lieu(){
			Nut<T>* temp = head;
			while( temp != NULL ){
				cout<< temp->get_data();
				temp = temp->get_next();
			}
		}

		int so_luong(){
			int dem = 0;
			Nut<T>* temp = head;
			while( temp != NULL ){
				dem++;
				temp = temp->get_next();
			}
			return dem;
		}

		void chen_vao_sau( Nut<T>* a, Nut<T>* b ){
			b->set_next( a->get_next() );
			a->set_next( b );
		}

		void them_tang_dan( Nut<T>* a ){
			if( head == NULL ){
				head = a;
				return;
			}
			Nut<T>* temp = head;
			int i = 0;
			while(  temp && a->get_data() > temp->get_data() ){
				temp = temp->get_next();
				i++;
			}
			chen_vao_vi_tri( i, a );
		}

		void chen_vao_vi_tri( int vi_tri, Nut<T>* a ){
			if( vi_tri == 0 ){
				them_vao_dau( a );
			}
			else if( vi_tri == so_luong() ){
				them_vao_cuoi( a );
			}
			else{
				Nut<T>* temp = head;
				int i = 1;
				while( i != vi_tri ){
					i++;
					temp = temp->get_next();
				}
				chen_vao_sau( temp, a );
			}
		}

		void chen_vao_sau_gia_tri( const T& gia_tri, const T& moi, bool (*cmp)(T*, T*)){
			Nut<T>* cur = tim_nut_thoa_dieu_kien( gia_tri, cmp );
			if( cur ){
				Nut<T>* newnode = new Nut<T>( moi) ;
				newnode->set_next( cur->get_next() );
				cur->set_next( newnode );
			}
		}

		void xoa_cuoi(){
			if( head ){
				if( head->get_next() == NULL ){
					deleteFirst();
					return;
				}
				Nut<T>* temp = head;
				Nut<T>* after = temp->get_next();
				while( after->get_next() ){
					temp = after;
					after = after->get_next();
				}
				temp->set_next( NULL );
				delete after;
			}
		}

		Nut<T>* tim_nut_thoa_dieu_kien( const T& gia_tri, bool (*cmp)(T*, T*) ){
			Nut<T>* temp = head;
			while( temp != NULL ){
				if( cmp( &temp->get_data(), (T*)&gia_tri ) ) break;
				temp = temp->get_next();
			}
			return temp;
		}

		void xoa_thoa_dk( const T& gia_tri, bool (*cmp)(T*, T*) ){
			if( head == NULL ) return;
			Nut<T>* temp = head;
			if( head->get_data() == gia_tri ){
				head = head->get_next();
				delete temp;
				return;
			}
			Nut<T>* cur = temp->get_next();
			while( cur != NULL ){
				if( cmp( &cur->get_data(), (T*)&gia_tri ) ){
					break;
				}
				temp = cur;
				cur = cur->get_next();
			}
			if( cur ){
				temp->set_next( cur->get_next() );
				delete cur;
			}
		}
};

template <class T>
class N{
	T data;
	N<T>* before;
	N<T>* next;
	public:
		N( T gia_tri ){
			data = gia_tri;
			before = NULL;
			next = NULL;
		}

		void set_before( N<T>* a ){
			before = a;
		}

		void set_next( N<T>* a ){
			next = a;
		}

		void set_data( T a ){
			data = a;
		}

		N<T>* get_before(){
			return before;
		}

		N<T>* get_next(){
			return next;
		}

		T& get_data(){
			return data;
		}
};

template <class T>
class LienKetDoi{
	N<T>* head;
	public:
		LienKetDoi(){
			head = NULL;
		}

		N<T>* get_head(){
			return head;
		}

		void addFirst( T gia_tri ){
			N<T>* newnode = new N<T>(gia_tri);
			newnode->set_next( head );
			head->set_before(newnode);
			head = newnode;
		}

		void addEnd( T gia_tri ){
			N<T>* newnode = new N<T>(gia_tri);
			N<T>* temp = head;
			if( temp == NULL ){
				head = newnode;
				return;
			}
			while( temp->get_next() != NULL ) temp = temp->get_next();
			temp->set_next( newnode );
			newnode->set_before(temp);
		}

		T deleteFirst(){
			if( head ){
				T result = head->get_data();
				N<T>* temp = head;
				head = head->get_next();
				head->set_before(NULL);
				delete temp;
				return result;
			}
		}

		void in_du_lieu(){
			N<T>* temp = head;
			while( temp != NULL ){
				cout<< temp->get_data();
				temp = temp->get_next();
			}
		}

		int so_luong(){
			int count = 0;
			N<T>* temp = head;
			while( temp != NULL ){
				count++;
				temp = temp->get_next();
			}
			return count;
		}

		void chen_vao_sau( N<T>* a, N<T>* b ){
			b->set_next( a->get_next() );
			b.set_before(a);
			a->get_next()->set_before(b);
			a->set_next( b );
		}

		void xoa_cuoi(){
			if( head ){
				if( head->get_next() == NULL ){
					deleteFirst();
					return;
				}
				N<T>* temp = head;
				N<T>* after = temp->get_next();
				while( after->get_next() ){
					temp = after;
					after = after->get_next();
				}
				temp->set_next( NULL );
				delete after;
			}
		}

		N<T>* tim_nut_thoa_dieu_kien( const T& gia_tri, bool (*cmp)(T*, T*) ){
			N<T>* temp = head;
			while( temp != NULL ){
				if( cmp( &temp->get_data(), (T*)&gia_tri ) ) break;
				temp = temp->get_next();
			}
			return temp;
		}

		void xoa_thoa_dk( const T& gia_tri, bool (*cmp)(T*, T*) ){
			if( head == NULL ) return;
			N<T>* temp = head;
			if( head->get_data() == gia_tri ){
				head = head->get_next();
				head->set_before(NULL);
				delete temp;
				return;
			}
			N<T>* cur = temp->get_next();
			while( cur != NULL ){
				if( cmp( &cur->get_data(), (T*)&gia_tri ) ){
					break;
				}
				temp = cur;
				cur = cur->get_next();
			}
			if( cur ){
				temp->set_next( cur->get_next() );
				if( cur->get_next() != NULL ){
					cur->get_next()->set_before(temp);
				}
				delete cur;
			}
		}
};

template <class T>
class Node{
	T data;
	Node<T>* left;
	Node<T>* right;
	public:
		Node( T gia_tri){
			data = gia_tri;
			left = NULL;
			right = NULL;
		}

		Node<T>* get_left(){
			return left;
		}

		Node<T>* get_right(){
			return right;
		}

		void set_left( Node<T>* a ){
			left = a;
		}

		void set_right( Node<T>* a ){
			right = a;
		}
		T get_data(){
			return data;
		}

		T& get_data_ref(){
			return data;
		}

		void set_data( T gia_tri ){
			data = gia_tri;
		}
};

template <class T>
class Binary{
	Node<T>* root;
	public:
		Binary(){
			root = NULL;
		}

		void set_root( Node<T>* p ){
			root = p;
		}

		Node<T>* get_root(){
			return root;
		}

		void add( T gia_tri ){
			Node<T>* newnode = new Node<T>(gia_tri);
			if( root == NULL ){
				root = newnode;
			}
			else{
				Node<T>* p = root;
				while( p->get_data() != gia_tri ){
					if( gia_tri < p->get_data() ){
						if( p->get_left() == NULL ){
							p->set_left(newnode);
							break;
						}
						p = p->get_left();
					}
					else{
						if( p->get_right() == NULL ){
							p->set_right(newnode);
							break;
						}
						p = p->get_right();
					}
				}
			}
		}

		void in_tien_to( Node<T>* p ){
			if( p != NULL ){
				cout<< p->get_data() << " ";
				in_tien_to( p->get_left() );
				in_tien_to( p->get_right() );
			}
		}

		void in_trung_to( Node<T>* p ){
			if( p != NULL ){
				in_trung_to( p->get_left() );
				cout<< p->get_data();
				in_trung_to( p->get_right() );
			}
		}

		int size( Node<T>* p ){
		    int count = 0;
			if( p != NULL ){
				count += 1;
				count += size( p->get_left() ) + size( p->get_right() );
			}
			return count;
		}

		Node<T>* find_binary( Node<T>* p, T gia_tri ){
			while( p != NULL ){
				if( p->get_data() == gia_tri) break;
				else if( p->get_data() < gia_tri ){
					p = p->get_right();
				}
				else p = p->get_left();

			}
			return p;
		}

		void erase_tree( Node<T>* p){
			if( p != NULL ){
				erase_tree( p->get_left() );
				erase_tree( p->get_right() );
				delete p;
			}
		}

		Node<T>* find_before( Node<T>* p, Node<T>* q ){
			while(true){
				if( p->get_data() > q->get_data() ){
					if( p->get_left() == q ) return p;
					p = p->get_left();
				}
				else{
					if( p->get_right() == q ) return p;
					p = p->get_right();
				}
			}
		}

		Node<T>* node_max( Node<T>* p ){
			while( true ){
				if( p->get_right() == NULL ) return p;
				p = p->get_right();
			}
		}

		void erase( T gia_tri ){
			Node<T>* p = find_binary(root, gia_tri );
			if( p ){
				if( !p->get_left() && !p->get_right() ){
					if( p == root ){
						delete p;
						root = NULL;
					}
					else{
						Node<T>* temp = find_before(root, p);
						if( temp->get_data() > p->get_data() ){
							delete temp->get_left();
							temp->set_left(NULL);
						}
						else{
							delete temp->get_right();
							temp->set_right(NULL);
						}
					}
				}
				else if( p->get_left() == NULL ){
					Node<T>* temp = find_before(root, p);
					if( temp->get_data() > p->get_data() ){
						temp->set_left( p->get_right() );
					}
					else{
						temp->set_right( p->get_right() );
					}
					delete p;
				}
				else{
					Node<T>* max = node_max( p->get_left() );
					Node<T>* node_before_max = find_before(p, max);
					if( node_before_max->get_data() > max->get_data() ){
						node_before_max->set_left( max->get_left() );
					}
					else{
						node_before_max->set_right( max->get_left() );
					}
					p->set_data(max->get_data());
					delete max;
				}
			}
		}
};

string in_hoa( string s ){
	for( int i = 0; i < s.length(); i++ ){
		if( s[i] >= 'a' && s[i] <= 'z'){
			s[i] = s[i] - 32;
		}
	}
	return s;
}

string tao_ma_sach( string ISBN, int so){
	string result;
	result += ISBN + chuyen_so_thanh_chuoi(so);
	return result;
}

string sinh_ISBN(){
	string result;
	for( int i = 0; i < 4; i++ ){
		char a = rand() %( 91 - 65) + 65;
		result += a;
	}
	return result;
}

bool match( string b, int start, string a ){
    if( a.length() == 0 ) return false;
	for( int i = 0; i < a.length(); i++ ){
		if( a[i] != b[start + i] ) return false;
	}
	return true;
}

bool nam_trong( string a, string b){
	if( a.length() > b.length() ){
		return false;
	}
	for( int i = 0; i <= b.length() - a.length(); i++ ){
		if( match(b, i, a) ) return true;
	}
	return false;
}

class MT{
	string ma_sach;
	NgayThang ngay_muon;
	NgayThang ngay_tra;
	int trang_thai;
	public:
		void set_ma_sach(string ms){
			ma_sach = ms;
		}

		void set_ngay_muon( NgayThang nm){
			ngay_muon = nm;
		}

		void set_ngay_tra( NgayThang nt ){
			ngay_tra = nt;
		}

		void set_trang_thai( int tt ){
			trang_thai = tt;
		}

		string get_ma_sach(){
			return ma_sach;
		}

		NgayThang get_ngay_muon(){
			return ngay_muon;
		}

		NgayThang get_ngay_tra(){
			return ngay_tra;
		}

		int get_trang_thai(){
			return trang_thai;
		}
};

class DG{
	int ma_the;
	string ho;
	string ten;
	int gioi_tinh;
	int trang_thai;
	LienKetDoi<MT> muon_tra;
	public:
		DG(){
			trang_thai = 1;
		}

		int get_ma_the(){
			return ma_the;
		}

		string get_ho(){
			return ho;
		}

		string get_ten(){
			return ten;
		}

		int get_gioi_tinh(){
            return gioi_tinh;
		}

		int get_trang_thai(){
            return trang_thai;
		}

		LienKetDoi<MT> get_muon_tra(){
			return muon_tra;
		}

		LienKetDoi<MT>& get_muon_tra_ref(){
			return muon_tra;
		}

		void set_ma_the( int a ){
			ma_the = a;
		}

		void set_ho( string s ){
			ho = s;
		}

		void set_ten( string s ){
			ten = s;
		}

		void set_gioi_tinh( int s ){
			gioi_tinh = s;
		}

		void set_trang_thai( int t ){
			trang_thai = t;
		}

		void set_muon_tra( LienKetDoi<MT> mt ){
			muon_tra = mt;
		}

		bool operator==(DG b){
			return ma_the == b.get_ma_the();
		}

		bool operator!=(DG b){
			return !((*this) == b);
		}

		bool operator>(DG b){
			return ma_the > b.get_ma_the();
		}

		bool operator<(DG b){
			return ma_the < b.get_ma_the();
		}

		friend ostream& operator<<(ostream& out, DG a){
			out<< setiosflags(ios::left) << setw(8) << a.ma_the << setw(23) << a.ho + " " + a.ten << setw(11) << a.gioi_tinh;
			if( a.trang_thai == 0 ) cout<< setw(5) << "Khoa\n";
			else cout<< setw(10) << "Hoat Dong\n";
			return out;
		}
};

class DMS{
	string ma_sach;
	int trang_thai;
	string vi_tri;
	public:
		DMS(){
			trang_thai = 0;
		}

		void set_ma_sach(string ms){
			ma_sach = ms;
		}

		void set_trang_thai( int tt ){
			trang_thai = tt;
		}

		void set_vi_tri(string vt){
			vi_tri = vt;
		}

		string get_ma_sach(){
			return ma_sach;
		}

		int get_trang_thai(){
			return trang_thai;
		}

		string get_vi_tri(){
			return vi_tri;
		}
};

class DS{
	string ten_sach;
	string ISBN;
	string tac_gia;
	string the_loai;
	int so_trang;
	int nam_xuat_ban;
	LienKetDon<DMS> danh_muc_sach;
	public:
		void set_ten_sach( string ts){
			ten_sach = ts;
		}

		void set_ISBN( string isbn ){
			ISBN = isbn;
		}

		void set_tac_gia( string tg){
			tac_gia = tg;
		}

		void set_the_loai( string tl){
			the_loai = tl;
		}

		void set_so_trang( int st){
			so_trang = st;
		}

		void set_nam_xuat_ban( int nsb){
			nam_xuat_ban = nsb;
		}

		void set_danh_muc_sach( LienKetDon<DMS> dms ){
			danh_muc_sach = dms;
		}

		string get_ten_sach(){
			return ten_sach;
		}

		string get_tac_gia(){
            return tac_gia;
		}

		string get_ISBN(){
			return ISBN;
		}

		string get_the_loai(){
			return the_loai;
		}

		int get_so_trang(){
            return so_trang;
		}

		int get_nam_xuat_ban(){
            return nam_xuat_ban;
		}

		LienKetDon<DMS> get_danh_muc_sach(){
			return danh_muc_sach;
		}

		friend ostream& operator<<(ostream& out, DS a){
			out<< setiosflags(ios::left) << setw(23) << a.ten_sach <<
			setw(7) << a.ISBN << setw(19) << a.tac_gia << setw(16) << a.the_loai <<
			setw(9) << a.so_trang << setw(4) << a.nam_xuat_ban << endl;
			return out;
		}
};

class DauSach{
	DS* arr[MAX_DS];
	int vi_tri;
	public:
		DauSach(){
			vi_tri = 0;
		}
		void doc_file(){
			ifstream ifs("DauSach.txt");
			int n;
			ifs >> n;
			ifs.ignore();
			for( int i = 0; i < n; i++ ){
				DS* temp = new DS;
				string ten_sach;
				getline(ifs, ten_sach);
				temp->set_ten_sach( ten_sach );

				string ISBN;
				getline(ifs, ISBN);
				temp->set_ISBN( ISBN );

				string tac_gia;
				getline(ifs, tac_gia);
				temp->set_tac_gia( tac_gia );

				string the_loai;
				getline(ifs, the_loai);
				temp->set_the_loai( the_loai );

				int so_trang;
				ifs>> so_trang;
				ifs.ignore();
				temp->set_so_trang(so_trang);

				int nam_xuat_ban;
				ifs>> nam_xuat_ban;
				ifs.ignore();
				temp->set_nam_xuat_ban( nam_xuat_ban );

				LienKetDon<DMS> danh_muc_sach;
				int so_sach;
				ifs>> so_sach;
				ifs.ignore();
				for( int j = 0; j < so_sach; j++ ){
					DMS current;
					string ma_sach;
					getline(ifs, ma_sach);
					current.set_ma_sach(ma_sach);

					int trang_thai;
					ifs >> trang_thai;
					ifs.ignore();
					current.set_trang_thai(trang_thai);

					string vi_tri;
					getline(ifs, vi_tri);
					current.set_vi_tri(vi_tri);

					danh_muc_sach.addEnd(current);
				}
				temp->set_danh_muc_sach(danh_muc_sach);
				if(vi_tri < MAX_DS){
					arr[vi_tri] = temp;
					vi_tri++;
				}
				else{
					delete temp;
					break;
				}
			}
		}

		bool trung_ISBN( string ISBN ){
			for( int i = 0; i < vi_tri; i++ ){
				if( arr[i]->get_ISBN() == ISBN ) return true;
			}
			return false;
		}

		void nhap_vi_tri_cua_cac_sach(int so_sach, string* mang_vi_tri){
            cleardevice();
            string huong_dan = "HUONG DAN: CHI NHAP CHU CAI, SO, KHOANG TRANG VA DAU PHAY";
            int width_huong_dan = textwidth("HUONG DAN: CHI NHAP CHU CAI, SO, KHOANG TRANG VA DAU PHAY") + 25;
            int height_huong_dan = 50;
            int x_huong_dan = getmaxx() / 2 - width_huong_dan / 2;
            int y_huong_dan = 100;
            int height_1 = 50;
            int khoang_giua = 50;
            int width_truoc = textwidth("TOI VI TRI SACH THU 12345") + 25;
            int height_truoc = 40;
            int width_nhap_vi_tri = 450;
            int height_nhap_vi_tri = height_truoc;
            int width_sau = width_truoc;
            int height_sau = height_truoc;
            int x_truoc = getmaxx() / 2 - (width_truoc + khoang_giua + width_nhap_vi_tri + khoang_giua + width_sau) / 2;
            int y_truoc = y_huong_dan + height_huong_dan + height_1;
            int x_nhap_vi_tri = x_truoc + width_truoc + khoang_giua;
            int y_nhap_vi_tri = y_truoc;
            int x_sau = x_nhap_vi_tri + width_nhap_vi_tri + khoang_giua;
            int y_sau = y_truoc;
            string nhap_xong = "DA NHAP XONG TAT CA VI TRI CUA CAC SACH";
            int width_nhap_xong = textwidth("DA NHAP XONG TAT CA VI TRI CUA CAC SACH") + 25;
            int height_nhap_xong = 50;
            int x_nhap_xong = getmaxx() / 2 - width_nhap_xong / 2;
            int y_nhap_xong = y_truoc + height_truoc + height_1;
            int sach_i = 1;
            while(true){
                string truoc = "TOI VI TRI SACH THU " + chuyen_so_thanh_chuoi(sach_i - 1);
                string sau = "TOI VI TRI SACH THU " + chuyen_so_thanh_chuoi(sach_i + 1);
                tao_khung(x_huong_dan, y_huong_dan, width_huong_dan, height_huong_dan, LIGHTCYAN, BLUE, chuyen_string_thanh_char(huong_dan), 0);
                tao_khung(x_nhap_xong, y_nhap_xong, width_nhap_xong, height_nhap_xong, LIGHTCYAN, BLUE, chuyen_string_thanh_char(nhap_xong), 0);
                tao_khung(x_nhap_vi_tri, y_nhap_vi_tri, width_nhap_vi_tri, height_nhap_vi_tri, LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_vi_tri[sach_i - 1]), -1);
                if( sach_i == 1){
                    tao_khung(x_sau, y_sau, width_sau, height_sau, LIGHTCYAN, BLUE, chuyen_string_thanh_char(sau), 0);
                }
                else if( sach_i == so_sach ){
                    tao_khung(x_truoc, y_truoc, width_truoc, height_truoc, LIGHTCYAN, BLUE, chuyen_string_thanh_char(truoc), 0);
                }
                else{
                    tao_khung(x_sau, y_sau, width_sau, height_sau, LIGHTCYAN, BLUE, chuyen_string_thanh_char(sau), 0);
                    tao_khung(x_truoc, y_truoc, width_truoc, height_truoc, LIGHTCYAN, BLUE, chuyen_string_thanh_char(truoc), 0);
                }
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_truoc, y_truoc, width_truoc, height_truoc) ){
                        if( sach_i > 1 ){
                            sach_i--;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_sau, y_sau, width_sau, height_sau) ){
                        if( sach_i < so_sach ){
                            sach_i++;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_nhap_vi_tri, y_nhap_vi_tri, width_nhap_vi_tri, height_nhap_vi_tri) ){
                        mang_vi_tri[sach_i - 1] = tao_khung_nhap(x_nhap_vi_tri, y_nhap_vi_tri, width_nhap_vi_tri, height_nhap_vi_tri, LIGHTCYAN, BLUE, -1, 25, nhap_vi_tri_sach);
                    }
                    else if( da_click_vao(x, y, x_nhap_xong, y_nhap_xong, width_nhap_xong, height_nhap_xong) ){
                        break;
                    }
                }
            }
            cleardevice();
		}

		void them_dau_sach(){
		    cleardevice();
            int so_dong_nhap = 6;
            int width_khung_nhap = 450;
            int height_khung_nhap = 450;
            int height_dong_nhap = 40;
            int khoang_cach_dong_nhap = 30;
            int khoang_giua = 100;
            int width_huong_dan = width_khung_nhap;
            int height_huong_dan = height_khung_nhap - (height_khung_nhap / so_dong_nhap - height_dong_nhap);
            int x_khung_nhap = getmaxx() / 2 - (width_khung_nhap + khoang_giua + width_huong_dan) / 2;
            int y_khung_nhap = 100;
            int x_huong_dan = x_khung_nhap + width_khung_nhap + khoang_giua;
            int y_huong_dan = y_khung_nhap;
            int mang_toa_do_khung_nhap[so_dong_nhap][2];
             for(int i = 0; i < so_dong_nhap; i++){
                mang_toa_do_khung_nhap[i][0] = x_khung_nhap;
                mang_toa_do_khung_nhap[i][1] = y_khung_nhap + i * (height_khung_nhap / so_dong_nhap);
             }

            int height_1 = 50;
            int x_thong_bao = x_khung_nhap;
            int y_thong_bao =  y_huong_dan + height_huong_dan + height_1;
            int width_thong_bao = 500;
            int height_thong_bao = 50;
            int x_save = x_khung_nhap;
            int y_save = y_thong_bao + height_thong_bao + height_1;
            int width_save = textwidth("SAVE") + 25;
            int height_save = 50;
            int x_thoat = x_save + width_save + khoang_giua;
            int y_thoat = y_save;
            int width_thoat = textwidth("THOAT") + 25;
            int height_thoat = height_save;

            int mang_ki_tu_toi_da[so_dong_nhap] = {25, 25, 20, 4, 9, 4};
            bool (*mang_ten_ham[so_dong_nhap])(int) = {chi_nhan_chu_cai_khoang_trong, chi_nhan_chu_cai_khoang_trong, chi_nhan_chu_cai_khoang_trong, chi_nhan_so, chi_nhan_so, chi_nhan_so};
            string MANGDONGNHAPBANDAU[so_dong_nhap] = {"NHAP TEN SACH(TOI DA 25 KI TU)", "NHAP TEN TAC GIA(TOI DA 25 KI TU)", "NHAP THE LOAI(TOI DA 20 KI TU)", "NHAP NAM XUAT BAN(TOI DA 4 KI TU)", "NHAP SO TRANG(TOI DA 9 KI TU)", "NHAP SO SACH CUA DAU SACH(TOI DA 4 KI TU)"};
            string mang_dong_nhap[so_dong_nhap];
            for(int i = 0; i < so_dong_nhap; i++){
                mang_dong_nhap[i] = MANGDONGNHAPBANDAU[i];
            }
            const int MAXSOSACH = 10000;
            string mang_vi_tri[MAXSOSACH];
            string thong_bao = "THONG BAO: ";
            DS* temp = NULL;
            bool khoi_tao_dau_sach = true;
            string ISBN;
            while(true){
                if( khoi_tao_dau_sach ){
                    temp = new DS;
                    khoi_tao_dau_sach = false;
                    while(true){
                        ISBN = sinh_ISBN();
                        if( !trung_ISBN( ISBN ) ){
                            temp->set_ISBN( ISBN );
                            break;
                        }
                    }
                }
                guide_table_dau_sach(x_huong_dan, y_huong_dan, width_huong_dan, height_huong_dan);
                for(int i = 0; i < so_dong_nhap; i++){
                    tao_khung(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_dong_nhap[i]), -1);
                }
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1);
                tao_khung(x_save, y_save, width_save, height_save, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SAVE"), 0);
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0);
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    for(int i = 0; i < so_dong_nhap - 1; i++){
                        if( da_click_vao(x, y, mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap) ){
                            mang_dong_nhap[i] = tao_khung_nhap(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, -1, mang_ki_tu_toi_da[i], mang_ten_ham[i]);
                        }
                    }
                    if( da_click_vao(x, y, mang_toa_do_khung_nhap[so_dong_nhap - 1][0], mang_toa_do_khung_nhap[so_dong_nhap - 1][1], width_khung_nhap, height_dong_nhap) ){
                        mang_dong_nhap[so_dong_nhap - 1] = tao_khung_nhap(mang_toa_do_khung_nhap[so_dong_nhap - 1][0], mang_toa_do_khung_nhap[so_dong_nhap - 1][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, -1, mang_ki_tu_toi_da[so_dong_nhap - 1], mang_ten_ham[so_dong_nhap - 1]);
                        int so_sach = chuyen_chuoi_thanh_so(mang_dong_nhap[so_dong_nhap - 1]);
                        if( so_sach > 0 ){
                             for(int i = 0; i < so_sach; i++){
                                mang_vi_tri[i] = "NHAP VI TRI CUA SACH SO " + chuyen_so_thanh_chuoi(i + 1) + "(TOI DA 25 KI TU)";
                             }
                             nhap_vi_tri_cua_cac_sach(so_sach, mang_vi_tri);
                        }
                    }
                    else if( da_click_vao(x, y, x_save, y_save, width_save, height_save) ){
                        bool nhap_day_du = true;
                        for(int i = 0; i < so_dong_nhap; i++){
                            if( mang_dong_nhap[i] == MANGDONGNHAPBANDAU[i] || mang_dong_nhap[i] == "" ){
                                nhap_day_du = false;
                                break;
                            }
                        }
                        if( nhap_day_du ){
                            int so_sach = chuyen_chuoi_thanh_so(mang_dong_nhap[so_dong_nhap - 1]);
                            if( so_sach > 0 ){
                                if(vi_tri < MAX_DS){
                                    string ten_sach = in_hoa(mang_dong_nhap[0]);
                                    temp->set_ten_sach( ten_sach );
                                    string tac_gia = in_hoa(mang_dong_nhap[1]);
                                    temp->set_tac_gia(tac_gia);
                                    string the_loai = in_hoa(mang_dong_nhap[2]);
                                    temp->set_the_loai(the_loai);
                                    int nam_xuat_ban = chuyen_chuoi_thanh_so(mang_dong_nhap[3]);
                                    temp->set_nam_xuat_ban(nam_xuat_ban);
                                    int so_trang = chuyen_chuoi_thanh_so(mang_dong_nhap[4]);
                                    temp->set_so_trang(so_trang);

                                    LienKetDon<DMS> danh_muc_sach;
                                    for( int i = 0; i < so_sach; i++ ){
                                        DMS current;
                                        string ma_sach = tao_ma_sach(ISBN, i + 1);
                                        current.set_ma_sach(ma_sach);
                                        string vi_tri = mang_vi_tri[i];
                                        current.set_vi_tri(vi_tri);
                                        danh_muc_sach.addEnd(current);
                                    }
                                    temp->set_danh_muc_sach(danh_muc_sach);

                                    arr[vi_tri] = temp;
                                    vi_tri++;
                                    cleardevice();
                                    thong_bao = "THONG BAO: THEM DAU SACH THANH CONG";
                                    khoi_tao_dau_sach = true;
                                    for(int i = 0; i < so_dong_nhap; i++){
                                        mang_dong_nhap[i] = MANGDONGNHAPBANDAU[i];
                                    }
                                }
                                else{
                                    delete temp;
                                    cleardevice();
                                    thong_bao = "THONG BAO: KHONG THE THEM DAU SACH VAO NUA";
                                }
                            }
                            else{
                                cleardevice();
                                thong_bao = "THONG BAO: SO SACH PHAI LON HON 0";
                            }
                        }
                        else{
                            cleardevice();
                            thong_bao = "THONG BAO: PHAI NHAP DAY DU CAC TRUONG";
                        }
                    }
                    else if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ){
                        break;
                    }
                }
            }
            cleardevice();
		}

		void xoa(int i){
            delete arr[i];
            for(int j = i; j < vi_tri - 1; j++){
                arr[j] = arr[j + 1];
            }
            vi_tri--;
		}

        int tim_ma_isbn( string string_ma_isbn){
            for(int i = 0; i < vi_tri; i++){
                if( arr[i]->get_ISBN() == string_ma_isbn ){
                    return i;
                }
            }
            return -1;
        }

        bool co_sach_dang_cho_muon(DS* ds){
            LienKetDon<DMS> danh_muc_sach = ds->get_danh_muc_sach();
            Nut<DMS>* p = danh_muc_sach.get_head();
            while( p != NULL ){
                if( p->get_data().get_trang_thai() == 1 ) return true;
                p = p->get_next();
            }
            return false;
        }

		void xoa_dau_sach(){
		    cleardevice();
			int line = 20;
			int so_trang;
			if( vi_tri % line == 0 ) so_trang = vi_tri / line;
			else  so_trang = vi_tri / line + 1;

			int x = 20;
			int y = 20;
			int height_trang_so_i = 40;
			int width_trang_so_i = textwidth("TRANG TRUOC") + 25;
			int y_trang_so_i = 700;
			int khoang_cach = 20;

			int x_trang_truoc = 200;
			int x_chu_trang = x_trang_truoc + width_trang_so_i + khoang_cach;
			int x_trang_sau = x_chu_trang + width_trang_so_i + khoang_cach;

			int x_nhap_ma_isbn = 1100;
			int y_nhap_ma_isbn = y;
			int width_nhap_ma_isbn = 450;
			int height_nhap_ma_isbn = 40;
			int x_thong_bao = x_nhap_ma_isbn;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_isbn + height_nhap_ma_isbn+ height_1;
			int width_thong_bao = width_nhap_ma_isbn;
			int height_thong_bao = height_nhap_ma_isbn;
			int x_thoat = x_nhap_ma_isbn;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_isbn = "NHAP MA ISBN (TOI DA 4 KI TU)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_the_loai_td(trang, line, x, y);
                tao_khung(x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG TRUOC"), 0);
                string trang_so_i = "TRANG " + chuyen_so_thanh_chuoi(trang);
                tao_khung(x_chu_trang, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_so_i), 0);
                tao_khung(x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG SAU"), 0);
                tao_khung(x_nhap_ma_isbn, y_nhap_ma_isbn, width_nhap_ma_isbn, height_nhap_ma_isbn, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_isbn), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    else if( da_click_vao(x, y, x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang > 1 ){
                            trang = trang - 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang < so_trang ){
                            trang = trang + 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_nhap_ma_isbn, y_nhap_ma_isbn, width_nhap_ma_isbn, height_nhap_ma_isbn) ){
                        string_ma_isbn = tao_khung_nhap(x_nhap_ma_isbn, y_nhap_ma_isbn, width_nhap_ma_isbn, height_nhap_ma_isbn, LIGHTCYAN, BLUE, -1, 4, chi_nhan_chu_cai );
                        string_ma_isbn = in_hoa(string_ma_isbn);
                        int result = tim_ma_isbn(string_ma_isbn);
                        if( result != -1 ){
                            if( !co_sach_dang_cho_muon(arr[result]) ){
                                xoa(result);
                                thong_bao = "THONG BAO: DA XOA DAU SACH THANH CONG";
                                cleardevice();
                            }
                            else{
                                thong_bao = "DAU SACH DANG CHO MUON!";
                                cleardevice();
                            }
                        }
                        else{
                            thong_bao = "THONG BAO: KHONG TIM THAY MA ISBN NAY";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		bool sua(int dau_sach_hien_tai){
            cleardevice();
            int so_dong_nhap = 6;
            int width_khung_nhap = 450;
            int height_khung_nhap = 450;
            int height_dong_nhap = 40;
            int khoang_cach_dong_nhap = 30;
            int khoang_giua = 100;
            int width_huong_dan = width_khung_nhap;
            int height_huong_dan = height_khung_nhap - (height_khung_nhap / so_dong_nhap - height_dong_nhap);
            int x_khung_nhap = getmaxx() / 2 - (width_khung_nhap + khoang_giua + width_huong_dan) / 2;
            int y_khung_nhap = 100;
            int x_huong_dan = x_khung_nhap + width_khung_nhap + khoang_giua;
            int y_huong_dan = y_khung_nhap;
            int mang_toa_do_khung_nhap[so_dong_nhap][2];
             for(int i = 0; i < so_dong_nhap; i++){
                mang_toa_do_khung_nhap[i][0] = x_khung_nhap;
                mang_toa_do_khung_nhap[i][1] = y_khung_nhap + i * (height_khung_nhap / so_dong_nhap);
             }

            int height_1 = 50;
            int x_thong_bao = x_khung_nhap;
            int y_thong_bao =  y_huong_dan + height_huong_dan + height_1;
            int width_thong_bao = 500;
            int height_thong_bao = 50;
            int x_save = x_khung_nhap;
            int y_save = y_thong_bao + height_thong_bao + height_1;
            int width_save = textwidth("SAVE") + 25;
            int height_save = 50;
            int x_thoat = x_save + width_save + khoang_giua;
            int y_thoat = y_save;
            int width_thoat = textwidth("THOAT") + 25;
            int height_thoat = height_save;

            int mang_ki_tu_toi_da[so_dong_nhap - 1] = {25, 25, 20, 4, 9};
            bool (*mang_ten_ham[so_dong_nhap - 1])(int) = {chi_nhan_chu_cai_khoang_trong, chi_nhan_chu_cai_khoang_trong, chi_nhan_chu_cai_khoang_trong, chi_nhan_so, chi_nhan_so};
            string MANGDONGNHAPBANDAU[so_dong_nhap] = {"NHAP TEN SACH(TOI DA 25 KI TU)", "NHAP TEN TAC GIA(TOI DA 25 KI TU)", "NHAP THE LOAI(TOI DA 20 KI TU)", "NHAP NAM XUAT BAN(TOI DA 4 KI TU)", "NHAP SO TRANG(TOI DA 9 KI TU)", "SUA VI TRI CUA CAC SACH"};
            string mang_dong_nhap[so_dong_nhap];
            for(int i = 0; i < so_dong_nhap; i++){
                mang_dong_nhap[i] = MANGDONGNHAPBANDAU[i];
            }
            int so_sach = arr[dau_sach_hien_tai]->get_danh_muc_sach().so_luong();
            string mang_vi_tri[so_sach];
            Nut<DMS>* p = arr[dau_sach_hien_tai]->get_danh_muc_sach().get_head();
            for(int i = 0; i < so_sach; i++){
                mang_vi_tri[i] = p->get_data().get_vi_tri();
                p = p->get_next();
            }
            string thong_bao = "THONG BAO: ";
            while(true){
                guide_table_dau_sach(x_huong_dan, y_huong_dan, width_huong_dan, height_huong_dan);
                for(int i = 0; i < so_dong_nhap; i++){
                    tao_khung(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_dong_nhap[i]), -1);
                }
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1);
                tao_khung(x_save, y_save, width_save, height_save, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SAVE"), 0);
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0);
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    for(int i = 0; i < so_dong_nhap - 1; i++){
                        if( da_click_vao(x, y, mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap) ){
                            mang_dong_nhap[i] = tao_khung_nhap(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, -1, mang_ki_tu_toi_da[i], mang_ten_ham[i]);
                        }
                    }
                    if( da_click_vao(x, y, mang_toa_do_khung_nhap[so_dong_nhap - 1][0], mang_toa_do_khung_nhap[so_dong_nhap - 1][1], width_khung_nhap, height_dong_nhap) ){
                         nhap_vi_tri_cua_cac_sach(so_sach, mang_vi_tri);
                    }
                    else if( da_click_vao(x, y, x_save, y_save, width_save, height_save) ){
                        bool nhap_day_du = true;
                        for(int i = 0; i < so_dong_nhap - 1; i++){
                            if( mang_dong_nhap[i] == MANGDONGNHAPBANDAU[i] || mang_dong_nhap[i] == "" ){
                                nhap_day_du = false;
                                break;
                            }
                        }
                        if( nhap_day_du ){
                            string ten_sach = in_hoa(mang_dong_nhap[0]);
                            arr[dau_sach_hien_tai]->set_ten_sach(ten_sach);
                            string tac_gia = in_hoa(mang_dong_nhap[1]);
                            arr[dau_sach_hien_tai]->set_tac_gia(tac_gia);
                            string the_loai = in_hoa(mang_dong_nhap[2]);
                            arr[dau_sach_hien_tai]->set_the_loai(the_loai);
                            int nam_xuat_ban = chuyen_chuoi_thanh_so(mang_dong_nhap[3]);
                            arr[dau_sach_hien_tai]->set_nam_xuat_ban(nam_xuat_ban);
                            int so_trang = chuyen_chuoi_thanh_so(mang_dong_nhap[4]);
                            arr[dau_sach_hien_tai]->set_so_trang(so_trang);

                            Nut<DMS>* p = arr[dau_sach_hien_tai]->get_danh_muc_sach().get_head();
                            for(int i = 0; i < so_sach; i++){
                                p->get_data().set_vi_tri(mang_vi_tri[i]);
                                p = p->get_next();
                            }
                            cleardevice();
                            return true;
                        }
                        else{
                            cleardevice();
                            thong_bao = "THONG BAO: PHAI NHAP DAY DU CAC TRUONG";
                        }
                    }
                    else if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ){
                        cleardevice();
                        return false;
                    }
                }
            }
		}

		void sua_dau_sach(){
		    cleardevice();
			int line = 20;
			int so_trang;
			if( vi_tri % line == 0 ) so_trang = vi_tri / line;
			else  so_trang = vi_tri / line + 1;

			int x = 20;
			int y = 20;
			int height_trang_so_i = 40;
			int width_trang_so_i = textwidth("TRANG TRUOC") + 25;
			int y_trang_so_i = 700;
			int khoang_cach = 20;

			int x_trang_truoc = 200;
			int x_chu_trang = x_trang_truoc + width_trang_so_i + khoang_cach;
			int x_trang_sau = x_chu_trang + width_trang_so_i + khoang_cach;

			int x_nhap_ma_isbn = 1100;
			int y_nhap_ma_isbn = y;
			int width_nhap_ma_isbn = 450;
			int height_nhap_ma_isbn = 40;
			int x_thong_bao = x_nhap_ma_isbn;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_isbn + height_nhap_ma_isbn+ height_1;
			int width_thong_bao = width_nhap_ma_isbn;
			int height_thong_bao = height_nhap_ma_isbn;
			int x_thoat = x_nhap_ma_isbn;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_isbn = "NHAP MA ISBN (TOI DA 4 KI TU)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_the_loai_td(trang, line, x, y);
                tao_khung(x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG TRUOC"), 0);
                string trang_so_i = "TRANG " + chuyen_so_thanh_chuoi(trang);
                tao_khung(x_chu_trang, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_so_i), 0);
                tao_khung(x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG SAU"), 0);
                tao_khung(x_nhap_ma_isbn, y_nhap_ma_isbn, width_nhap_ma_isbn, height_nhap_ma_isbn, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_isbn), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    else if( da_click_vao(x, y, x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang > 1 ){
                            trang = trang - 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang < so_trang ){
                            trang = trang + 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_nhap_ma_isbn, y_nhap_ma_isbn, width_nhap_ma_isbn, height_nhap_ma_isbn) ){
                        string_ma_isbn = tao_khung_nhap(x_nhap_ma_isbn, y_nhap_ma_isbn, width_nhap_ma_isbn, height_nhap_ma_isbn, LIGHTCYAN, BLUE, -1, 4, chi_nhan_chu_cai );
                        string_ma_isbn = in_hoa(string_ma_isbn);
                        int result = tim_ma_isbn(string_ma_isbn);
                        if( result != -1 ){
                            if( sua(result) ){
                                thong_bao = "THONG BAO: SUA DAU SACH THANH CONG";
                            }
                            else{
                                thong_bao = "THONG BAO:";
                            }
                        }
                        else{
                            thong_bao = "THONG BAO: KHONG TIM THAY MA ISBN NAY";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		void sap_xep(bool (*cmp)(DS, DS)){
			for(int i = 0; i < vi_tri; i++ ){
				for(int j = 0; j < vi_tri - 1 - i; j++){
					if( !cmp(*arr[j], *arr[j + 1]) ){
						DS* temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
				}
			}
		}

		DS* lay_ds_tu_ma_sach(string ma_sach){
            for(int i = 0; i < vi_tri; i++){
                Nut<DMS>* p = arr[i]->get_danh_muc_sach().get_head();
                while(p){
                    if( p->get_data().get_ma_sach() == ma_sach ){
                        return arr[i];
                    }
                    p = p->get_next();
                }
            }
		}

		void in_trang_the_loai_td(int trang, int line, int x, int y){
            int height = 30;
            int width_ISBN = 100;
            int width_ten_sach = 300;
            int width_tac_gia = 250;
            int width_the_loai = 200;
            int width_so_trang = 150;
            int width_nam_xuat_ban = 50;

            int x_temp = x;
            tao_khung(x_temp, y, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("ISBN"), -1);
            x_temp += width_ISBN;
            tao_khung(x_temp, y, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TEN SACH"), -1);
            x_temp += width_ten_sach;
            tao_khung(x_temp, y, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TAC GIA"), -1);
            x_temp += width_tac_gia;
            tao_khung(x_temp, y, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THE LOAI"), -1);
            x_temp += width_the_loai;
            tao_khung(x_temp, y, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SO TRANG"), -1);
            x_temp += width_so_trang;
            tao_khung(x_temp, y, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("NAM"), -1);

            for(int i = (trang - 1) * line; i < (trang - 1) * line + line; i++){
                if( i < vi_tri ){
                    x_temp = x;
                    y += height;
                    tao_khung(x_temp, y, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i]->get_ISBN()), -1);
                    x_temp += width_ISBN;
                    tao_khung(x_temp, y, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i]->get_ten_sach()), -1);
                    x_temp += width_ten_sach;
                    tao_khung(x_temp, y, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i]->get_tac_gia()), -1);
                    x_temp += width_tac_gia;
                    tao_khung(x_temp, y, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i]->get_the_loai()), -1);
                    x_temp += width_the_loai;
                    string so_trang = chuyen_so_thanh_chuoi(arr[i]->get_so_trang());
                    tao_khung(x_temp, y, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so_trang), -1);
                    x_temp += width_so_trang;
                    string nam_xuat_ban = chuyen_so_thanh_chuoi(arr[i]->get_nam_xuat_ban());
                    tao_khung(x_temp, y, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(nam_xuat_ban), -1);
                }
                else{
                    x_temp = x;
                    y += height;
                    tao_khung(x_temp, y, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ISBN;
                    tao_khung(x_temp, y, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ten_sach;
                    tao_khung(x_temp, y, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_tac_gia;
                    tao_khung(x_temp, y, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_the_loai;
                    tao_khung(x_temp, y, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_so_trang;
                    tao_khung(x_temp, y, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                }
            }
        }

		void in_td_theo_the_loai(bool (*cmp)(DS, DS)){
		    cleardevice();
		    sap_xep(cmp);
			int line = 20;
			int so_trang;
			if( vi_tri % line == 0 ) so_trang = vi_tri / line;
			else  so_trang = vi_tri / line + 1;

			int x = 20;
			int y = 20;
			int height_trang_so_i = 40;
			int width_trang_so_i = textwidth("TRANG TRUOC") + 25;
			int y_trang_so_i = 700;
			int khoang_cach = 20;

			int x_trang_truoc = 200;
			int x_chu_trang = x_trang_truoc + width_trang_so_i + khoang_cach;
			int x_trang_sau = x_chu_trang + width_trang_so_i + khoang_cach;

			int x_thoat = 1200;
			int y_thoat = getmaxy() / 2;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;

			int trang = 1;
			while(true){
                in_trang_the_loai_td(trang, line, x, y);
                tao_khung(x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG TRUOC"), 0);
                string trang_so_i = "TRANG " + chuyen_so_thanh_chuoi(trang);
                tao_khung(x_chu_trang, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_so_i), 0);
                tao_khung(x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG SAU"), 0);
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    else if( da_click_vao(x, y, x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang > 1 ){
                            trang = trang - 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang < so_trang ){
                            trang = trang + 1;
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		void in_trang_tim_thay(int trang, int line, int x, int y, MangMotChieu<string>& s){
            int x_temp;
            int height = 30;
            int width_ISBN = 100;
            int width_ten_sach = 300;
            int width_tac_gia = 250;
            int width_the_loai = 200;
            int width_so_trang = 150;
            int width_nam_xuat_ban = 50;
            int width_tong = width_ISBN + width_ten_sach + width_tac_gia + width_the_loai + width_so_trang + width_nam_xuat_ban;
            int tam = (x + x + width_tong - 1 ) / 2;
            int width_ma_sach = tam - x + 1;
            int width_trang_thai = x + width_tong - tam - 1;

            for(int i = (trang - 1) * line; i < (trang - 1) * line + line; i++){
                if( i < s.size() ){
                    x_temp = x;
                    if( chuoi_toan_so(s[i]) ){
                        tao_khung(x_temp, y, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[chuyen_chuoi_thanh_so(s[i])]->get_ISBN()), -1);
                        x_temp += width_ISBN;
                        tao_khung(x_temp, y, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[chuyen_chuoi_thanh_so(s[i])]->get_ten_sach()), -1);
                        x_temp += width_ten_sach;
                        tao_khung(x_temp, y, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[chuyen_chuoi_thanh_so(s[i])]->get_tac_gia()), -1);
                        x_temp += width_tac_gia;
                        tao_khung(x_temp, y, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[chuyen_chuoi_thanh_so(s[i])]->get_the_loai()), -1);
                        x_temp += width_the_loai;
                        string so_trang = chuyen_so_thanh_chuoi(arr[chuyen_chuoi_thanh_so(s[i])]->get_so_trang());
                        tao_khung(x_temp, y, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so_trang), -1);
                        x_temp += width_so_trang;
                        string nam_xuat_ban = chuyen_so_thanh_chuoi(arr[chuyen_chuoi_thanh_so(s[i])]->get_nam_xuat_ban());
                        tao_khung(x_temp, y, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(nam_xuat_ban), -1);
                    }
                    else{
                        char c = s[i][0];
                        string temp;
                        for(int j = 1; j < s[i].length(); j++){
                            temp += s[i][j];
                        }
                        tao_khung(x_temp, y, width_ma_sach , height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(temp), -1);
                        x_temp += width_ma_sach;
                        string trang_thai;
                        if( c == '0' ) trang_thai = "CHUA CHO MUON";
                        else if( c == '1' ) trang_thai = "DA CHO MUON";
                        else trang_thai = "DA THANH LY";
                        tao_khung(x_temp, y, width_trang_thai , height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_thai), -1);
                    }
                    y += height;
                }
                else{
                    x_temp = x;
                    tao_khung(x_temp, y, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ISBN;
                    tao_khung(x_temp, y, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ten_sach;
                    tao_khung(x_temp, y, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_tac_gia;
                    tao_khung(x_temp, y, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_the_loai;
                    tao_khung(x_temp, y, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_so_trang;
                    tao_khung(x_temp, y, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    y += height;
                }
            }
		}

		void nhap_ngay_thang(NgayThang& ngay_muon){
             cleardevice();
             int width_ngay = 200;
             int height_ngay = 40;
             int khoang_giua = 50;
             int x_ngay = getmaxx() / 2 - (3 * width_ngay + 2 * khoang_giua) / 2;
             int y_ngay = 100;
             int x_thang = x_ngay + width_ngay + khoang_giua;
             int x_nam = x_thang + width_ngay + khoang_giua;
             int height_1 = 50;
             int width_thong_bao = 450;
             int height_thong_bao = 50;
             int x_thong_bao = x_ngay;
             int y_thong_bao = y_ngay + height_ngay + height_1;
             int width_save = textwidth("SAVE") + 25;
             int height_save = 50;
             int x_save = x_ngay;
             int y_save = y_thong_bao + height_thong_bao + height_1;
             string ngay = "NHAP NGAY";
             string thang = "NHAP THANG";
             string nam = "NHAP NAM";
             string thong_bao = "THONG BAO:";

             while(true){
                tao_khung(x_ngay, y_ngay, width_ngay, height_ngay, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ngay), -1);
                tao_khung(x_thang, y_ngay, width_ngay, height_ngay, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thang), -1);
                tao_khung(x_nam, y_ngay, width_ngay, height_ngay, LIGHTCYAN, BLUE, chuyen_string_thanh_char(nam), -1);
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1);
                tao_khung(x_save, y_save, width_save, height_save, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SAVE"), -1);
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_ngay, y_ngay, width_ngay, height_ngay) ){
                        ngay = tao_khung_nhap(x_ngay, y_ngay, width_ngay, height_ngay, LIGHTCYAN, BLUE, -1, 2, chi_nhan_so);
                    }
                    else if( da_click_vao(x, y, x_thang, y_ngay, width_ngay, height_ngay) ){
                        thang = tao_khung_nhap(x_thang, y_ngay, width_ngay, height_ngay, LIGHTCYAN, BLUE, -1, 2, chi_nhan_so);
                    }
                    else if( da_click_vao(x, y, x_nam, y_ngay, width_ngay, height_ngay) ){
                        nam = tao_khung_nhap(x_nam, y_ngay, width_ngay, height_ngay, LIGHTCYAN, BLUE, -1, 4, chi_nhan_so);
                    }
                    else if( da_click_vao(x, y, x_save, y_save, width_save, height_save) ){
                        ngay_muon.set_ngay(chuyen_chuoi_thanh_so(ngay));
                        ngay_muon.set_thang(chuyen_chuoi_thanh_so(thang));
                        ngay_muon.set_nam(chuyen_chuoi_thanh_so(nam));
                        if(ngay_muon.ngay_hop_le()){
                            break;
                        }
                        else{
                            thong_bao = "THONG BAO: NGAY THANG NAM CHUA HOP LE";
                        }
                    }
                }
             }
             cleardevice();
		}

		void in_dau_sach_tim_thay( MangMotChieu<string>& s, bool muon, Node<DG>* p, int so_sach_dang_muon){
            cleardevice();
			int line = 21;
			int so_trang;
			if( s.size() % line == 0 ) so_trang = s.size() / line;
			else  so_trang = s.size() / line + 1;

			int x = 20;
			int y = 20;
			int height_trang_so_i = 40;
			int width_trang_so_i = textwidth("TRANG TRUOC") + 25;
			int y_trang_so_i = 700;
			int khoang_cach = 20;

			int x_trang_truoc = 200;
			int x_chu_trang = x_trang_truoc + width_trang_so_i + khoang_cach;
			int x_trang_sau = x_chu_trang + width_trang_so_i + khoang_cach;

			int x_nhap_ma_sach = 1100;
			int y_nhap_ma_sach = y;
			int width_nhap_ma_sach = 450;
			int height_nhap_ma_sach = 40;
			int x_thong_bao = x_nhap_ma_sach;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_sach + height_nhap_ma_sach+ height_1;
			int width_thong_bao = width_nhap_ma_sach;
			int height_thong_bao = height_nhap_ma_sach;
			int x_thoat = x_nhap_ma_sach;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_sach = "NHAP MA SACH MUON MUON(TOI DA 8 KI TU)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_tim_thay(trang, line, x, y, s);
                tao_khung(x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG TRUOC"), 0);
                string trang_so_i = "TRANG " + chuyen_so_thanh_chuoi(trang);
                tao_khung(x_chu_trang, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_so_i), 0);
                tao_khung(x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG SAU"), 0);
                if(muon){
                    tao_khung(x_nhap_ma_sach, y_nhap_ma_sach, width_nhap_ma_sach, height_nhap_ma_sach, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_sach), -1 );
                    tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                }
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    else if( da_click_vao(x, y, x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang > 1 ){
                            trang = trang - 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang < so_trang ){
                            trang = trang + 1;
                            cleardevice();
                        }
                    }
                    if(muon){
                        if( da_click_vao(x, y, x_nhap_ma_sach, y_nhap_ma_sach, width_nhap_ma_sach, height_nhap_ma_sach) ){
                            string_ma_sach = tao_khung_nhap(x_nhap_ma_sach, y_nhap_ma_sach, width_nhap_ma_sach, height_nhap_ma_sach, LIGHTCYAN, BLUE, -1, 8, chi_nhan_chu_cai_so);
                            string_ma_sach = in_hoa(string_ma_sach);
                            if( so_sach_dang_muon == 3 ){
                                thong_bao = "THONG BAO: CHI DUOC MUON TOI DA 3 CUON";
                                cleardevice();
                            }
                            else{
                                int result = tim_ma_sach(string_ma_sach);
                                if( result == 1 ){
                                   set_ma_sach(string_ma_sach, 1);
                                   MT temp;
                                   temp.set_ma_sach(string_ma_sach);
                                   temp.set_trang_thai(0);
                                   NgayThang ngay_muon;
                                   nhap_ngay_thang(ngay_muon);
                                   temp.set_ngay_muon(ngay_muon);
                                   p->get_data_ref().get_muon_tra_ref().addEnd(temp);
                                   so_sach_dang_muon++;
                                   thong_bao = "MUON THANH CONG";
                                }
                                else if( result == -1 ){
                                    thong_bao = "THONG BAO: MA SACH DA CHO MUON";
                                    cleardevice();
                                }
                                else{
                                    thong_bao = "THONG BAO: MA SACH KHONG TON TAI";
                                    cleardevice();
                                }
                            }
                        }
                    }
                }
			}
			cleardevice();
		}

		bool tim_thay_ten_sach(string ten_sach, MangMotChieu<string>& s){
            bool result = false;
			for( int i = 0; i < vi_tri; i++ ){
				if( nam_trong( ten_sach, arr[i]->get_ten_sach() ) ){
					result = true;
					s.push_back(chuyen_so_thanh_chuoi(i));
					LienKetDon<DMS> danh_muc_sach = arr[i]->get_danh_muc_sach();
					Nut<DMS>* p = danh_muc_sach.get_head();
					while( p != NULL ){
                        string tt_ms = chuyen_so_thanh_chuoi(p->get_data().get_trang_thai()) + p->get_data().get_ma_sach();
						s.push_back(tt_ms);
						p = p->get_next();
					}
				}
			}
			return result;
		}

		void tim_sach(bool muon = false, Node<DG>* p = NULL, int so_sach_dang_muon = 0){
		    cleardevice();
			int line = 20;
			int so_trang;
			if( vi_tri % line == 0 ) so_trang = vi_tri / line;
			else  so_trang = vi_tri / line + 1;

			int x = 20;
			int y = 20;
			int height_trang_so_i = 40;
			int width_trang_so_i = textwidth("TRANG TRUOC") + 25;
			int y_trang_so_i = 700;
			int khoang_cach = 20;

			int x_trang_truoc = 200;
			int x_chu_trang = x_trang_truoc + width_trang_so_i + khoang_cach;
			int x_trang_sau = x_chu_trang + width_trang_so_i + khoang_cach;

			int x_nhap_ten_sach = 1100;
			int y_nhap_ten_sach = y;
			int width_nhap_ten_sach = 450;
			int height_nhap_ten_sach = 40;
			int x_thong_bao = x_nhap_ten_sach;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ten_sach + height_nhap_ten_sach+ height_1;
			int width_thong_bao = width_nhap_ten_sach;
			int height_thong_bao = height_nhap_ten_sach;
			int x_thoat = x_nhap_ten_sach;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ten_sach = "NHAP TEN SACH(TOI DA 25 KI TU)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_the_loai_td(trang, line, x, y);
                tao_khung(x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG TRUOC"), 0);
                string trang_so_i = "TRANG " + chuyen_so_thanh_chuoi(trang);
                tao_khung(x_chu_trang, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_so_i), 0);
                tao_khung(x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG SAU"), 0);
                tao_khung(x_nhap_ten_sach, y_nhap_ten_sach, width_nhap_ten_sach, height_nhap_ten_sach, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ten_sach), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    else if( da_click_vao(x, y, x_trang_truoc, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang > 1 ){
                            trang = trang - 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_trang_sau, y_trang_so_i, width_trang_so_i, height_trang_so_i) ){
                        if( trang < so_trang ){
                            trang = trang + 1;
                            cleardevice();
                        }
                    }
                    else if( da_click_vao(x, y, x_nhap_ten_sach, y_nhap_ten_sach, width_nhap_ten_sach, height_nhap_ten_sach) ){
                        string_ten_sach = tao_khung_nhap(x_nhap_ten_sach, y_nhap_ten_sach, width_nhap_ten_sach, height_nhap_ten_sach, LIGHTCYAN, BLUE, -1, 25, chi_nhan_chu_cai_so_khoang_trong );
                        string_ten_sach = chuanHoaChuoi(in_hoa(string_ten_sach));
                        MangMotChieu<string> s;
                        if( tim_thay_ten_sach(string_ten_sach, s) ){
                            in_dau_sach_tim_thay(s, muon, p, so_sach_dang_muon);
                            thong_bao = "THONG BAO:";
                        }
                        else{
                            thong_bao = "THONG BAO: KHONG CO SACH NAY";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		int tim_ma_sach( string ma_sach ){
			for( int i = 0; i < vi_tri; i++ ){
				LienKetDon<DMS> danh_muc_sach = arr[i]->get_danh_muc_sach();
				Nut<DMS>* p = danh_muc_sach.get_head();
				while( p != NULL ){
					if( p->get_data().get_ma_sach() == ma_sach ){
						if( p->get_data().get_trang_thai() == 0 ){
							return 1;
						}
						else return -1;
					}
					p = p->get_next();
				}
			}
			return 0;
		}

		void set_ma_sach( string ma_sach, int so ){
			for( int i = 0; i < vi_tri; i++ ){
				LienKetDon<DMS> danh_muc_sach = arr[i]->get_danh_muc_sach();
				Nut<DMS>* p = danh_muc_sach.get_head();
				while( p != NULL ){
					if( p->get_data().get_ma_sach() == ma_sach ){
						p->get_data().set_trang_thai(so);
					}
					p = p->get_next();
				}
			}
		}

		void in_10_dau_sach_muon_nhieu_nhat( bool (*cmp)(DS, DS) ){
			cleardevice();
		    sap_xep(cmp);
			int line = 10;
			int x = 250;
			int y = 20;
			int x_thoat = getmaxx() / 2;
			int y_thoat = getmaxy() / 2;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;

			while(true){
                in_trang_the_loai_td(1, line, x, y);
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                }
			}
			cleardevice();
		}
};




class DocGia{
	Binary<DG> doc_gia;
	public:
		void doc_file(){
			ifstream ifs("DocGia.txt");
			int n;
			ifs >> n;
			ifs.ignore();
			for( int i = 0; i < n; i++ ){
				DG temp;
				int ma_the;
				ifs>> ma_the;
				ifs.ignore();
				temp.set_ma_the( ma_the );

				string ho;
				getline(ifs, ho);
				temp.set_ho( ho );

				string ten;
				getline(ifs, ten);
				temp.set_ten( ten );

				int gioi_tinh;
				ifs>> gioi_tinh;
				ifs.ignore();
				temp.set_gioi_tinh( gioi_tinh );

				int trang_thai;
				ifs>> trang_thai;
				ifs.ignore();
				temp.set_trang_thai(trang_thai);

				LienKetDoi<MT> muon_tra;
				int so_muon_tra;
				ifs>> so_muon_tra;
				ifs.ignore();
				for( int i = 0; i < so_muon_tra; i++ ){
					MT mt;
					string ma_sach;
					getline(ifs, ma_sach);
					mt.set_ma_sach(ma_sach);

					int ngay, thang, nam;
					ifs>> ngay;
					ifs.ignore();
					ifs>> thang;
					ifs.ignore();
					ifs>> nam;
					ifs.ignore();
					NgayThang nt(ngay, thang, nam);
					mt.set_ngay_muon(nt);

					ifs>> ngay;
					ifs.ignore();
					ifs>> thang;
					ifs.ignore();
					ifs>> nam;
					ifs.ignore();
					NgayThang nt2(ngay, thang, nam);
					mt.set_ngay_tra(nt2);

					int trang_thai;
					ifs>> trang_thai;
					ifs.ignore();
					mt.set_trang_thai(trang_thai);

					muon_tra.addEnd(mt);
				}
				temp.set_muon_tra(muon_tra);
				doc_gia.add( temp );
			}
		}

		bool trung_ma_the( int ma_the ){
			Node<DG>* p = doc_gia.get_root();
			while( p != NULL ){
				if( p->get_data().get_ma_the() == ma_the ) return true;
				else if( p->get_data().get_ma_the() > ma_the ){
					p = p->get_left();
				}
				else p = p->get_right();
			}
			return false;
		}
		void them_doc_gia(){
		    cleardevice();
            int so_dong_nhap = 3;
            int width_khung_nhap = 400;
            int height_khung_nhap = 400;
            int height_dong_nhap = 40;
            int khoang_cach_dong_nhap = 30;
            int khoang_giua = 100;
            int width_huong_dan = width_khung_nhap;
            int height_huong_dan = height_khung_nhap - (height_khung_nhap / so_dong_nhap - height_dong_nhap);
            int x_khung_nhap = getmaxx() / 2 - (width_khung_nhap + khoang_giua + width_huong_dan) / 2;
            int y_khung_nhap = 100;
            int x_huong_dan = x_khung_nhap + width_khung_nhap + khoang_giua;
            int y_huong_dan = y_khung_nhap;
            int mang_toa_do_khung_nhap[so_dong_nhap][2];
             for(int i = 0; i < so_dong_nhap; i++){
                mang_toa_do_khung_nhap[i][0] = x_khung_nhap;
                mang_toa_do_khung_nhap[i][1] = y_khung_nhap + i * (height_khung_nhap / so_dong_nhap);
             }

            int height_1 = 50;
            int x_thong_bao = x_khung_nhap;
            int y_thong_bao =  y_huong_dan + height_huong_dan + height_1;
            int width_thong_bao = 500;
            int height_thong_bao = 50;
            int x_save = x_khung_nhap;
            int y_save = y_thong_bao + height_thong_bao + height_1;
            int width_save = textwidth("SAVE") + 25;
            int height_save = 50;
            int x_thoat = x_save + width_save + khoang_giua;
            int y_thoat = y_save;
            int width_thoat = textwidth("THOAT") + 25;
            int height_thoat = height_save;

            int mang_ki_tu_toi_da[so_dong_nhap] = {20, 10, 1};
            bool (*mang_ten_ham[so_dong_nhap])(int) = {chi_nhan_chu_cai_khoang_trong, chi_nhan_chu_cai, chi_nhan_0_1};
            string MANGDONGNHAPBANDAU[so_dong_nhap] = {"NHAP HO(TOI DA 20 KI TU)", "NHAP TEN(TOI DA 10 KI TU)", "NHAP PHAI(0:NAM, 1:NU)"};
            string mang_dong_nhap[so_dong_nhap];
            for(int i = 0; i < so_dong_nhap; i++){
                mang_dong_nhap[i] = MANGDONGNHAPBANDAU[i];
            }
            string thong_bao = "THONG BAO: ";
            DG temp;
            bool khoi_tao_ma_the = true;
            while(true){
                if( khoi_tao_ma_the ){
                    khoi_tao_ma_the = false;
                    int ma_the;
                    while(true){
                        ma_the = rand();
                        if( !trung_ma_the( ma_the ) ){
                            break;
                        }
                    }
                    temp.set_ma_the( ma_the );
                }
                guide_table_doc_gia(x_huong_dan, y_huong_dan, width_huong_dan, height_huong_dan);
                for(int i = 0; i < so_dong_nhap; i++){
                    tao_khung(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_dong_nhap[i]), -1);
                }
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1);
                tao_khung(x_save, y_save, width_save, height_save, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SAVE"), 0);
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0);
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    for(int i = 0; i < so_dong_nhap; i++){
                        if( da_click_vao(x, y, mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap) ){
                            mang_dong_nhap[i] = tao_khung_nhap(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, -1, mang_ki_tu_toi_da[i], mang_ten_ham[i]);
                        }
                    }
                    if( da_click_vao(x, y, x_save, y_save, width_save, height_save) ){
                        bool nhap_day_du = true;
                        for(int i = 0; i < so_dong_nhap; i++){
                            if( mang_dong_nhap[i] == MANGDONGNHAPBANDAU[i] || mang_dong_nhap[i] == "" ){
                                nhap_day_du = false;
                                break;
                            }
                        }
                        if( nhap_day_du ){
                            string ho = in_hoa(mang_dong_nhap[0]);
                            temp.set_ho(ho);
                            string ten = in_hoa(mang_dong_nhap[1]);
                            temp.set_ten( ten );
                            if( mang_dong_nhap[2] == "0" ){
                                temp.set_gioi_tinh(0);
                            }
                            else{
                                temp.set_gioi_tinh(1);
                            }
                            doc_gia.add( temp );
                            cleardevice();
                            thong_bao = "THONG BAO: THEM DOC GIA THANH CONG";
                            for(int i = 0; i < so_dong_nhap; i++){
                                mang_dong_nhap[i] = MANGDONGNHAPBANDAU[i];
                            }
                            khoi_tao_ma_the = true;
                        }
                        else{
                            cleardevice();
                            thong_bao = "THONG BAO: PHAI NHAP DAY DU CAC TRUONG";
                        }
                    }
                    else if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ){
                        break;
                    }
                }
            }
            cleardevice();
		}

		void xoa_doc_gia(){
		    cleardevice();
			int line = 20;
			int so_doc_gia = doc_gia.size(doc_gia.get_root());
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_nhap_ma_the = 1000;
			int y_nhap_ma_the = y;
			int width_nhap_ma_the = 500;
			int height_nhap_ma_the = 40;
			int x_thong_bao = x_nhap_ma_the;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_the + height_nhap_ma_the + height_1;
			int width_thong_bao = width_nhap_ma_the;
			int height_thong_bao = height_nhap_ma_the;
			int x_thoat = x_nhap_ma_the;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_the = "NHAP MA THE(CHI NHAN SO)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_ma_the_td(trang, line, x, y);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_the), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                    if( da_click_vao(x, y, x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the) ){
                        string_ma_the = tao_khung_nhap(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, -1, 5, chi_nhan_so );
                        int ma_the = chuyen_chuoi_thanh_so(string_ma_the);
                        DG temp;
                        temp.set_ma_the(ma_the);
                        Node<DG>* p;
                        p = doc_gia.find_binary( doc_gia.get_root(), temp );
                        if( p ){
                            if( so_sach_dang_muon(p) == 0 ){
                                doc_gia.erase( temp );
                                thong_bao = "THONG BAO: DA XOA THANH CONG";
                                cleardevice();
                            }
                            else{
                                thong_bao = "THONG BAO: DANG MUON SACH, KHONG THE XOA!";
                                cleardevice();
                            }
                        }
                        else{
                            thong_bao = "THONG BAO: MA DOC GIA KHONG TON TAI";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		void sua(string& h, string& t, int& gt, int& tt, bool& save){
            cleardevice();
            int so_dong_nhap = 4;
            int width_khung_nhap = 400;
            int height_khung_nhap = 400;
            int height_dong_nhap = 40;
            int khoang_cach_dong_nhap = 30;
            int khoang_giua = 100;
            int width_huong_dan = width_khung_nhap;
            int height_huong_dan = height_khung_nhap - (height_khung_nhap / so_dong_nhap - height_dong_nhap);
            int x_khung_nhap = getmaxx() / 2 - (width_khung_nhap + khoang_giua + width_huong_dan) / 2;
            int y_khung_nhap = 100;
            int x_huong_dan = x_khung_nhap + width_khung_nhap + khoang_giua;
            int y_huong_dan = y_khung_nhap;
            int mang_toa_do_khung_nhap[so_dong_nhap][2];
             for(int i = 0; i < so_dong_nhap; i++){
                mang_toa_do_khung_nhap[i][0] = x_khung_nhap;
                mang_toa_do_khung_nhap[i][1] = y_khung_nhap + i * (height_khung_nhap / so_dong_nhap);
             }

            int height_1 = 50;
            int x_thong_bao = x_khung_nhap;
            int y_thong_bao =  y_huong_dan + height_huong_dan + height_1;
            int width_thong_bao = 500;
            int height_thong_bao = 50;
            int x_save = x_khung_nhap;
            int y_save = y_thong_bao + height_thong_bao + height_1;
            int width_save = textwidth("SAVE") + 25;
            int height_save = 50;
            int x_thoat = x_save + width_save + khoang_giua;
            int y_thoat = y_save;
            int width_thoat = textwidth("THOAT") + 25;
            int height_thoat = height_save;

            int mang_ki_tu_toi_da[so_dong_nhap] = {20, 10, 1, 1};
            bool (*mang_ten_ham[so_dong_nhap])(int) = {chi_nhan_chu_cai_khoang_trong, chi_nhan_chu_cai, chi_nhan_0_1, chi_nhan_0_1};
            string MANGDONGNHAPBANDAU[so_dong_nhap] = {"NHAP HO(TOI DA 20 KI TU)", "NHAP TEN(TOI DA 10 KI TU)", "NHAP PHAI(0:NAM, 1:NU)", "NHAP TRANG THAI(0:KHOA, 1:HOAT DONG)"};
            string mang_dong_nhap[so_dong_nhap];
            for(int i = 0; i < so_dong_nhap; i++){
                mang_dong_nhap[i] = MANGDONGNHAPBANDAU[i];
            }
            string thong_bao = "THONG BAO: ";
            while(true){
                guide_table_doc_gia(x_huong_dan, y_huong_dan, width_huong_dan, height_huong_dan);
                for(int i = 0; i < so_dong_nhap; i++){
                    tao_khung(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_dong_nhap[i]), -1);
                }
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1);
                tao_khung(x_save, y_save, width_save, height_save, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SAVE"), 0);
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0);
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    for(int i = 0; i < so_dong_nhap; i++){
                        if( da_click_vao(x, y, mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap) ){
                            mang_dong_nhap[i] = tao_khung_nhap(mang_toa_do_khung_nhap[i][0], mang_toa_do_khung_nhap[i][1], width_khung_nhap, height_dong_nhap, LIGHTCYAN, BLUE, -1, mang_ki_tu_toi_da[i], mang_ten_ham[i]);
                        }
                    }
                    if( da_click_vao(x, y, x_save, y_save, width_save, height_save) ){
                        bool nhap_day_du = true;
                        for(int i = 0; i < so_dong_nhap; i++){
                            if( mang_dong_nhap[i] == MANGDONGNHAPBANDAU[i] || mang_dong_nhap[i] == "" ){
                                nhap_day_du = false;
                                break;
                            }
                        }
                        if( nhap_day_du ){
                            save = true;
                            h = in_hoa(mang_dong_nhap[0]);
                            t = in_hoa(mang_dong_nhap[1]);
                            if( mang_dong_nhap[2] == "0" ){
                                gt = 0;
                            }
                            else{
                                gt = 1;
                            }
                            if(  mang_dong_nhap[3] == "0" ){
                                tt = 0;
                            }
                            else{
                                tt = 1;
                            }
                            break;
                        }
                        else{
                            cleardevice();
                            thong_bao = "THONG BAO: PHAI NHAP DAY DU CAC TRUONG";
                        }
                    }
                    else if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ){
                        break;
                    }
                }
            }
            cleardevice();
		}

		void sua_doc_gia(){
			cleardevice();
			int line = 20;
			int so_doc_gia = doc_gia.size(doc_gia.get_root());
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_nhap_ma_the = 1000;
			int y_nhap_ma_the = y;
			int width_nhap_ma_the = 500;
			int height_nhap_ma_the = 40;
			int x_thong_bao = x_nhap_ma_the;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_the + height_nhap_ma_the + height_1;
			int width_thong_bao = width_nhap_ma_the;
			int height_thong_bao = height_nhap_ma_the;
			int x_thoat = x_nhap_ma_the;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_the = "NHAP MA THE(CHI NHAN SO)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_ma_the_td(trang, line, x, y);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_the), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                    if( da_click_vao(x, y, x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the) ){
                        string_ma_the = tao_khung_nhap(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, -1, 5, chi_nhan_so );
                        int ma_the = chuyen_chuoi_thanh_so(string_ma_the);
                        DG temp;
                        temp.set_ma_the(ma_the);
                        Node<DG>* p;
                        p = doc_gia.find_binary( doc_gia.get_root(), temp );
                        if( p ){
                            string ho, ten;
                            int gioi_tinh, trang_thai;
                            bool save = false;
                            sua(ho, ten, gioi_tinh, trang_thai, save);
                            if( save ){
                                p->get_data_ref().set_ho( ho );
                                p->get_data_ref().set_ten( ten );
                                p->get_data_ref().set_gioi_tinh( gioi_tinh );
                                p->get_data_ref().set_trang_thai(trang_thai);
                                thong_bao = "THONG BAO: DA SUA THANH CONG";
                                //cleardevice();
                            }
                            else{
                                thong_bao = "THONG BAO:";
                            }
                        }
                        else{
                            thong_bao = "THONG BAO: MA DOC GIA KHONG TON TAI";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

        void in_trang_ma_the_td(int trang, int line, int x, int y){
            MangMotChieu<DG> arr;
            day_du_lieu_vao_mang(doc_gia.get_root(), arr);

            int height = 30;
            int width_ma_the = 150;
            int width_ho = 300;
            int width_ten = 200;
            int width_phai = 150;
            int width_trang_thai = 150;

            int x_temp = x;
            tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("MA "), -1);
            x_temp += width_ma_the;
            tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("HO"), -1);
            x_temp += width_ho;
            tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TEN"), -1);
            x_temp += width_ten;
            tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("PHAI"), -1);
            x_temp += width_phai;
            tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG THAI"), -1);

            for(int i = (trang - 1) * line; i < (trang - 1) * line + line; i++){
                if( i < arr.size() ){
                    x_temp = x;
                    y += height;
                    string ma_the = chuyen_so_thanh_chuoi(arr[i].get_ma_the());
                    tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ma_the), -1);
                    x_temp += width_ma_the;
                    tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i].get_ho()), -1);
                    x_temp += width_ho;
                    tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i].get_ten()), -1);
                    x_temp += width_ten;
                    string phai;
                    if( arr[i].get_gioi_tinh() == 0 ) phai = "NAM";
                    else phai = "NU";
                    tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(phai), -1);
                    x_temp += width_phai;
                    string trang_thai;
                    if( arr[i].get_trang_thai() == 0 ) trang_thai = "KHOA";
                    else trang_thai = "HOAT DONG";
                    tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_thai), -1);
                }
                else{
                    x_temp = x;
                    y += height;
                    tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ma_the;
                    tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ho;
                    tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ten;
                    tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_phai;
                    tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                }
            }
        }

        void in_trang_ho_ten_td(int trang, int line, int x, int y, bool (*cmp)(DG, DG)){
            MangMotChieu<DG> arr;
            day_du_lieu_vao_mang(doc_gia.get_root(), arr);
            arr.sap_xep(cmp);

            int height = 30;
            int width_ma_the = 150;
            int width_ho = 300;
            int width_ten = 200;
            int width_phai = 150;
            int width_trang_thai = 150;

            int x_temp = x;
            tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("MA THE"), -1);
            x_temp += width_ma_the;
            tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("HO"), -1);
            x_temp += width_ho;
            tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TEN"), -1);
            x_temp += width_ten;
            tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("PHAI"), -1);
            x_temp += width_phai;
            tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG THAI"), -1);

            for(int i = (trang - 1) * line; i < (trang - 1) * line + line; i++){
                if( i < arr.size() ){
                    x_temp = x;
                    y += height;
                    string ma_the = chuyen_so_thanh_chuoi(arr[i].get_ma_the());
                    tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ma_the), -1);
                    x_temp += width_ma_the;
                    tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i].get_ho()), -1);
                    x_temp += width_ho;
                    tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(arr[i].get_ten()), -1);
                    x_temp += width_ten;
                    string phai;
                    if( arr[i].get_gioi_tinh() == 0 ) phai = "NAM";
                    else phai = "NU";
                    tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(phai), -1);
                    x_temp += width_phai;
                    string trang_thai;
                    if( arr[i].get_trang_thai() == 0 ) trang_thai = "KHOA";
                    else trang_thai = "HOAT DONG";
                    tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_thai), -1);
                }
                else{
                    x_temp = x;
                    y += height;
                    tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ma_the;
                    tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ho;
                    tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ten;
                    tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_phai;
                    tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                }
            }
        }

		void in_td_theo_ma_dg(){
		    cleardevice();
			int line = 20;
			int so_doc_gia = doc_gia.size(doc_gia.get_root());
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_thoat = 1050;
			int y_thoat = getmaxy() / 2;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;

			int trang = 1;
			while(true){
                in_trang_ma_the_td(trang, line, x, y);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                }
			}
			cleardevice();
		}

		void day_du_lieu_vao_mang(Node<DG>* p, MangMotChieu<DG>& arr){
			if( p ){
                day_du_lieu_vao_mang( p->get_left(), arr );
				arr.push_back(p->get_data());
				day_du_lieu_vao_mang( p->get_right(), arr );
			}
		}

		void in_td_theo_ho_ten(bool (*cmp)(DG, DG)){
		    cleardevice();
			int line = 20;
			int so_doc_gia = doc_gia.size(doc_gia.get_root());
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach + 1);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_thoat = 1050;
			int y_thoat = getmaxy() / 2;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;

			int trang = 1;
			while(true){
                in_trang_ho_ten_td(trang, line, x, y, cmp);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                }
			}
			cleardevice();
		}

		int so_sach_dang_muon( Node<DG>* p ){
            N<MT>* temp = p->get_data().get_muon_tra().get_head();
			int so_sach_muon = 0;
			while(temp){
				if(temp->get_data().get_trang_thai() == 0 ){
					so_sach_muon++;
				}
				temp = temp->get_next();
			}
			return so_sach_muon;
		}

		int co_the_muon( Node<DG>* p ){
			N<MT>* temp = p->get_data().get_muon_tra().get_head();
			int so_sach_muon, so_sach_qua_han;
			so_sach_muon = so_sach_qua_han = 0;
			while(temp){
				if(temp->get_data().get_trang_thai() == 0 ){
					so_sach_muon++;

					time_t baygio = time(0);
					tm *ltm = localtime(&baygio);
					NgayThang ngay_hien_tai(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
					NgayThang ngay_muon = temp->get_data().get_ngay_muon();

					if( ngay_hien_tai.kc_giua_2_ngay(ngay_muon) > 7 ) so_sach_qua_han++;
				}
				temp = temp->get_next();
			}
			if( so_sach_muon < 3 && so_sach_qua_han == 0 ) return 1;
			else if( so_sach_muon == 3 ) return 0;
			else return -1;
		}

		void muon_sach( DauSach& dau_sach){
		    cleardevice();
			int line = 20;
			int so_doc_gia = doc_gia.size(doc_gia.get_root());
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_nhap_ma_the = 1000;
			int y_nhap_ma_the = y;
			int width_nhap_ma_the = 500;
			int height_nhap_ma_the = 40;
			int x_thong_bao = x_nhap_ma_the;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_the + height_nhap_ma_the + height_1;
			int width_thong_bao = width_nhap_ma_the;
			int height_thong_bao = height_nhap_ma_the;
			int x_thoat = x_nhap_ma_the;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_the = "NHAP MA THE(CHI NHAN SO)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_ma_the_td(trang, line, x, y);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_the), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                    if( da_click_vao(x, y, x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the) ){
                        string_ma_the = tao_khung_nhap(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, -1, 5, chi_nhan_so );
                        int ma_the = chuyen_chuoi_thanh_so(string_ma_the);
                        DG temp;
                        temp.set_ma_the(ma_the);
                        Node<DG>* p;
                        p = doc_gia.find_binary( doc_gia.get_root(), temp );
                        if( p ){
                            int result = co_the_muon(p);
                            if( result == 1 ){
                                int so_sach_muon = so_sach_dang_muon(p);
                                bool muon = true;
                                dau_sach.tim_sach(muon, p, so_sach_muon);
                                thong_bao = "THONG BAO:";
                            }
                            else if( result == 0 ){
                                thong_bao = "THONG BAO: CHI DUOC MUON TOI DA 3 CUON";
                                cleardevice();
                            }
                            else{
                                thong_bao = "THONG BAO: PHAI TRA SACH MUON QUA HAN TRUOC";
                                cleardevice();
                            }
                        }
                        else{
                            thong_bao = "THONG BAO: MA DOC GIA KHONG TON TAI";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		void tra(DauSach& dau_sach, Node<DG>* p){
		    cleardevice();
		    string cac_sach_dang_muon = "CAC SACH BAN DANG MUON";
            int width_cac_sach_dang_muon = textwidth("CAC SACH BAN DANG MUON") + 25;
            int height_cac_sach_dang_muon = 50;
            int x_cac_sach_dang_muon = getmaxx() / 2 - width_cac_sach_dang_muon / 2;
            int y_cac_sach_dang_muon = 100;

            int x = 200;
            int y_goc = 200;
            int x_temp, y_temp = y_goc;
            int height = 40;
            int width_ISBN = 100;
            int width_ten_sach = 300;
            int width_tac_gia = 250;
            int width_the_loai = 200;
            int width_so_trang = 150;
            int width_nam_xuat_ban = 50;
            int khoang_giua = 50;
            int width_tra = textwidth("TRA") + 25;
            int height_tra = height - 5;


            int width_thoat = textwidth("THOAT") + 25;
            int height_thoat = 50;
            int x_thoat = getmaxx() / 2 - width_thoat / 2;
            int y_thoat = getmaxy() / 2;

            MangMotChieu<string> mang_toa_do_va_ma_sach;
            MangMotChieu<N<MT>*> mang_con_tro_mt;
            int so_sach_muon = so_sach_dang_muon(p);
            bool khoi_tao = true;
            while(true){
                tao_khung(x_cac_sach_dang_muon, y_cac_sach_dang_muon, width_cac_sach_dang_muon, height_cac_sach_dang_muon, LIGHTCYAN, BLUE, chuyen_string_thanh_char(cac_sach_dang_muon), 0);
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0);
                x_temp = x;
                tao_khung(x_temp, y_goc, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("ISBN"), -1);
                x_temp += width_ISBN;
                tao_khung(x_temp, y_goc, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TEN SACH"), -1);
                x_temp += width_ten_sach;
                tao_khung(x_temp, y_goc, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TAC GIA"), -1);
                x_temp += width_tac_gia;
                tao_khung(x_temp, y_goc, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THE LOAI"), -1);
                x_temp += width_the_loai;
                tao_khung(x_temp, y_goc, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SO TRANG"), -1);
                x_temp += width_so_trang;
                tao_khung(x_temp, y_goc, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("NAM"), -1);
                if(khoi_tao){
                    khoi_tao = false;
                    if( so_sach_muon > 0 ){
                        N<MT>* dau = p->get_data().get_muon_tra().get_head();
                        while(dau){
                            if( dau->get_data().get_trang_thai() == 0 ){
                                string ma_sach = dau->get_data().get_ma_sach();
                                DS* ds = dau_sach.lay_ds_tu_ma_sach(ma_sach);
                                x_temp = x;
                                y_temp += height;
                                tao_khung(x_temp, y_temp, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_ISBN()), -1);
                                x_temp += width_ISBN;
                                tao_khung(x_temp, y_temp, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_ten_sach()), -1);
                                x_temp += width_ten_sach;
                                tao_khung(x_temp, y_temp, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_tac_gia()), -1);
                                x_temp += width_tac_gia;
                                tao_khung(x_temp, y_temp, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_the_loai()), -1);
                                x_temp += width_the_loai;
                                string so_trang = chuyen_so_thanh_chuoi(ds->get_so_trang());
                                tao_khung(x_temp, y_temp, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so_trang), -1);
                                x_temp += width_so_trang;
                                string nam_xuat_ban = chuyen_so_thanh_chuoi(ds->get_nam_xuat_ban());
                                tao_khung(x_temp, y_temp, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(nam_xuat_ban), -1);
                                x_temp += width_nam_xuat_ban + khoang_giua;
                                tao_khung(x_temp, y_temp, width_tra, height_tra, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRA"), 0);

                                mang_toa_do_va_ma_sach.push_back(chuyen_so_thanh_chuoi(x_temp));
                                mang_toa_do_va_ma_sach.push_back(chuyen_so_thanh_chuoi(y_temp));
                                mang_toa_do_va_ma_sach.push_back(ma_sach);
                                mang_con_tro_mt.push_back(dau);
                            }
                            dau = dau->get_next();
                        }
                    }
                }
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ){
                        break;
                    }
                    for(int i = 0; i < so_sach_muon; i++){
                        if( da_click_vao(x, y, chuyen_chuoi_thanh_so(mang_toa_do_va_ma_sach[i * 3]), chuyen_chuoi_thanh_so(mang_toa_do_va_ma_sach[i * 3 + 1]), width_tra, height_tra) ){
                            NgayThang ngay_tra;
                            dau_sach.nhap_ngay_thang(ngay_tra);
                            string ma_sach = mang_toa_do_va_ma_sach[i * 3 + 2];
                            dau_sach.set_ma_sach(ma_sach, 0);
                            mang_con_tro_mt[i]->get_data().set_ngay_tra(ngay_tra);
                            mang_con_tro_mt[i]->get_data().set_trang_thai(1);
                            so_sach_muon--;
                            y_temp = y_goc;
                            khoi_tao = true;
                            mang_toa_do_va_ma_sach.resize(0);
                            mang_con_tro_mt.resize(0);
                            cleardevice();
                            break;
                        }
                    }
                }
            }
            cleardevice();
		}

		void tra_sach( DauSach& dau_sach ){
		    cleardevice();
			int line = 20;
			int so_doc_gia = doc_gia.size(doc_gia.get_root());
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_nhap_ma_the = 1000;
			int y_nhap_ma_the = y;
			int width_nhap_ma_the = 500;
			int height_nhap_ma_the = 40;
			int x_thong_bao = x_nhap_ma_the;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_the + height_nhap_ma_the + height_1;
			int width_thong_bao = width_nhap_ma_the;
			int height_thong_bao = height_nhap_ma_the;
			int x_thoat = x_nhap_ma_the;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_the = "NHAP MA THE(CHI NHAN SO)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_ma_the_td(trang, line, x, y);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_the), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                    if( da_click_vao(x, y, x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the) ){
                        string_ma_the = tao_khung_nhap(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, -1, 5, chi_nhan_so );
                        int ma_the = chuyen_chuoi_thanh_so(string_ma_the);
                        DG temp;
                        temp.set_ma_the(ma_the);
                        Node<DG>* p;
                        p = doc_gia.find_binary( doc_gia.get_root(), temp );
                        if( p ){
                            int so_sach_muon = so_sach_dang_muon(p);
                            if( so_sach_muon > 0 ){
                                tra(dau_sach, p);
                                thong_bao = "THONG BAO:";
                            }
                            else{
                                thong_bao = "THONG BAO: BAN KHONG CO MUON SACH NAO";
                                cleardevice();
                            }
                        }
                        else{
                            thong_bao = "THONG BAO: MA DOC GIA KHONG TON TAI";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		void xem(DauSach dau_sach, Node<DG>* p){
            cleardevice();
		    string cac_sach_dang_muon = "CAC SACH BAN DANG MUON";
            int width_cac_sach_dang_muon = textwidth("CAC SACH BAN DANG MUON") + 25;
            int height_cac_sach_dang_muon = 50;
            int x_cac_sach_dang_muon = getmaxx() / 2 - width_cac_sach_dang_muon / 2;
            int y_cac_sach_dang_muon = 100;

            int height = 40;
            int width_ISBN = 100;
            int width_ten_sach = 300;
            int width_tac_gia = 250;
            int width_the_loai = 200;
            int width_so_trang = 150;
            int width_nam_xuat_ban = 50;
            int x = getmaxx() / 2 - (width_ISBN + width_ten_sach + width_tac_gia + width_the_loai + width_so_trang + width_nam_xuat_ban) / 2;
            int y_goc = 200;
            int x_temp, y_temp = y_goc;

            int width_thoat = textwidth("THOAT") + 25;
            int height_thoat = 50;
            int x_thoat = getmaxx() / 2 - width_thoat / 2;
            int y_thoat = getmaxy() / 2;

            while(true){
                tao_khung(x_cac_sach_dang_muon, y_cac_sach_dang_muon, width_cac_sach_dang_muon, height_cac_sach_dang_muon, LIGHTCYAN, BLUE, chuyen_string_thanh_char(cac_sach_dang_muon), 0);
                x_temp = x;
                y_temp = y_goc;
                tao_khung(x_temp, y_goc, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("ISBN"), -1);
                x_temp += width_ISBN;
                tao_khung(x_temp, y_goc, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TEN SACH"), -1);
                x_temp += width_ten_sach;
                tao_khung(x_temp, y_goc, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TAC GIA"), -1);
                x_temp += width_tac_gia;
                tao_khung(x_temp, y_goc, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THE LOAI"), -1);
                x_temp += width_the_loai;
                tao_khung(x_temp, y_goc, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("SO TRANG"), -1);
                x_temp += width_so_trang;
                tao_khung(x_temp, y_goc, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("NAM"), -1);
                N<MT>* dau = p->get_data().get_muon_tra().get_head();
                while(dau){
                    if( dau->get_data().get_trang_thai() == 0 ){
                        string ma_sach = dau->get_data().get_ma_sach();
                        DS* ds = dau_sach.lay_ds_tu_ma_sach(ma_sach);
                        x_temp = x;
                        y_temp += height;
                        tao_khung(x_temp, y_temp, width_ISBN, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_ISBN()), -1);
                        x_temp += width_ISBN;
                        tao_khung(x_temp, y_temp, width_ten_sach, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_ten_sach()), -1);
                        x_temp += width_ten_sach;
                        tao_khung(x_temp, y_temp, width_tac_gia, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_tac_gia()), -1);
                        x_temp += width_tac_gia;
                        tao_khung(x_temp, y_temp, width_the_loai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ds->get_the_loai()), -1);
                        x_temp += width_the_loai;
                        string so_trang = chuyen_so_thanh_chuoi(ds->get_so_trang());
                        tao_khung(x_temp, y_temp, width_so_trang, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so_trang), -1);
                        x_temp += width_so_trang;
                        string nam_xuat_ban = chuyen_so_thanh_chuoi(ds->get_nam_xuat_ban());
                        tao_khung(x_temp, y_temp, width_nam_xuat_ban, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(nam_xuat_ban), -1);
                    }
                    dau = dau->get_next();
                }
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0);
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ){
                        break;
                    }
                }
            }
            cleardevice();
		}

		void xem_sach_dang_muon(DauSach dau_sach){
		    cleardevice();
			int line = 20;
			int so_doc_gia = doc_gia.size(doc_gia.get_root());
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_nhap_ma_the = 1000;
			int y_nhap_ma_the = y;
			int width_nhap_ma_the = 500;
			int height_nhap_ma_the = 40;
			int x_thong_bao = x_nhap_ma_the;
			int height_1 = 50;
			int y_thong_bao = y_nhap_ma_the + height_nhap_ma_the + height_1;
			int width_thong_bao = width_nhap_ma_the;
			int height_thong_bao = height_nhap_ma_the;
			int x_thoat = x_nhap_ma_the;
			int y_thoat = y_thong_bao + height_thong_bao + height_1;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;
			string string_ma_the = "NHAP MA THE(CHI NHAN SO)";
			string thong_bao = "THONG BAO:";

			int trang = 1;
			while(true){
                in_trang_ma_the_td(trang, line, x, y);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, chuyen_string_thanh_char(string_ma_the), -1 );
                tao_khung(x_thong_bao, y_thong_bao, width_thong_bao, height_thong_bao, LIGHTCYAN, BLUE, chuyen_string_thanh_char(thong_bao), -1 );
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                    if( da_click_vao(x, y, x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the) ){
                        string_ma_the = tao_khung_nhap(x_nhap_ma_the, y_nhap_ma_the, width_nhap_ma_the, height_nhap_ma_the, LIGHTCYAN, BLUE, -1, 5, chi_nhan_so );
                        int ma_the = chuyen_chuoi_thanh_so(string_ma_the);
                        DG temp;
                        temp.set_ma_the(ma_the);
                        Node<DG>* p;
                        p = doc_gia.find_binary( doc_gia.get_root(), temp );
                        if( p ){
                            int so_sach_muon = so_sach_dang_muon(p);
                            if( so_sach_muon > 0 ){
                                xem(dau_sach, p);
                                thong_bao = "THONG BAO:";
                            }
                            else{
                                thong_bao = "THONG BAO: BAN KHONG CO MUON SACH NAO";
                                cleardevice();
                            }
                        }
                        else{
                            thong_bao = "THONG BAO: MA DOC GIA KHONG TON TAI";
                            cleardevice();
                        }
                    }
                }
			}
			cleardevice();
		}

		void truyen_mang_qua_han( Node<DG>* p, MangMotChieu<DG>& mang_qua_han ){
			if( p ){
				N<MT>* dau = p->get_data().get_muon_tra().get_head();
				while(dau){
					if( dau->get_data().get_trang_thai() == 0 ){
						time_t baygio = time(0);
						tm *ltm = localtime(&baygio);
						NgayThang ngay_hien_tai(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
						if( ngay_hien_tai.kc_giua_2_ngay(dau->get_data().get_ngay_muon() ) > 7 ){
							mang_qua_han.push_back(p->get_data());
							break;
						}
					}
					dau = dau->get_next();
				}
				truyen_mang_qua_han(p->get_left(), mang_qua_han);
				truyen_mang_qua_han(p->get_right(), mang_qua_han);
			}
		}

		void in_trang_dg_muon_qua_han(int trang, int line, int x, int y, MangMotChieu<DG> mang_qua_han){
            int height = 30;
            int width_ma_the = 150;
            int width_ho = 300;
            int width_ten = 200;
            int width_phai = 150;
            int width_trang_thai = 150;

            int x_temp = x;
            tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("MA THE"), -1);
            x_temp += width_ma_the;
            tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("HO"), -1);
            x_temp += width_ho;
            tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TEN"), -1);
            x_temp += width_ten;
            tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("PHAI"), -1);
            x_temp += width_phai;
            tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG THAI"), -1);

            for(int i = (trang - 1) * line; i < (trang - 1) * line + line; i++){
                if( i < mang_qua_han.size() ){
                    x_temp = x;
                    y += height;
                    string ma_the = chuyen_so_thanh_chuoi(mang_qua_han[i].get_ma_the());
                    tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(ma_the), -1);
                    x_temp += width_ma_the;
                    tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_qua_han[i].get_ho()), -1);
                    x_temp += width_ho;
                    tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(mang_qua_han[i].get_ten()), -1);
                    x_temp += width_ten;
                    string phai;
                    if( mang_qua_han[i].get_gioi_tinh() == 0 ) phai = "NAM";
                    else phai = "NU";
                    tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(phai), -1);
                    x_temp += width_phai;
                    string trang_thai;
                    if( mang_qua_han[i].get_trang_thai() == 0 ) trang_thai = "KHOA";
                    else trang_thai = "HOAT DONG";
                    tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(trang_thai), -1);
                }
                else{
                    x_temp = x;
                    y += height;
                    tao_khung(x_temp, y, width_ma_the, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ma_the;
                    tao_khung(x_temp, y, width_ho, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ho;
                    tao_khung(x_temp, y, width_ten, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_ten;
                    tao_khung(x_temp, y, width_phai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                    x_temp += width_phai;
                    tao_khung(x_temp, y, width_trang_thai, height, LIGHTCYAN, BLUE, chuyen_string_thanh_char(""), -1);
                }
            }
		}

		void in_cac_doc_gia_muon_sach_qua_han_giam_dan( bool (*cmp)(DG, DG) ){
		    cleardevice();
			MangMotChieu<DG> mang_qua_han;
			truyen_mang_qua_han(doc_gia.get_root(), mang_qua_han);
			mang_qua_han.sap_xep(cmp);

			int line = 20;
			int so_doc_gia = mang_qua_han.size();
			int so_trang;
			if( so_doc_gia % line == 0 ) so_trang = so_doc_gia / line;
			else  so_trang = so_doc_gia / line + 1;

			int x = 20;
			int y = 20;
			int x_chu_trang = x;
			int y_chu_trang = 700;
			int width_chu_trang = textwidth("TRANG:") + 25;
			int width_trang = 50;
			int height_trang = 40;
			int khoang_cach = 20;
			int x_trang = x + width_chu_trang + khoang_cach + 1;
			int toa_do_trang[so_trang][2];
			for(int i = 0; i < so_trang; i++ ){
                toa_do_trang[i][0] = x_trang + i * (width_trang + khoang_cach + 1);
                toa_do_trang[i][1] = y_chu_trang;
			}
			int x_thoat = 1050;
			int y_thoat = getmaxy() / 2;
			int width_thoat = textwidth("THOAT") + 25;
			int height_thoat = textheight("THOAT") + 25;

			int trang = 1;
			while(true){
                in_trang_dg_muon_qua_han(trang, line, x, y, mang_qua_han);
                tao_khung(x, y_chu_trang, width_chu_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char("TRANG:"), -1);
                for(int i = 0; i < so_trang; i++ ){
                    string so = chuyen_so_thanh_chuoi(i + 1);
                    tao_khung(toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang, LIGHTCYAN, BLUE, chuyen_string_thanh_char(so), 0);
                }
                tao_khung(x_thoat, y_thoat, width_thoat, height_thoat, LIGHTCYAN, BLUE, chuyen_string_thanh_char("THOAT"), 0 );
                delay(100);
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if( da_click_vao(x, y, x_thoat, y_thoat, width_thoat, height_thoat) ) break;
                    for(int i = 0; i < so_trang; i++ ){
                        if( da_click_vao(x, y, toa_do_trang[i][0], toa_do_trang[i][1], width_trang, height_trang) ){
                            trang = i + 1;
                            cleardevice();
                            break;
                        }
                    }
                }
			}
			cleardevice();
		}
};

bool ten_ho_tang_dan(DG a, DG b){
	if( a.get_ten() < b.get_ten() ) return true;
	else if( a.get_ten() > b.get_ten() ) return false;
	else{
		if( a.get_ho() < b.get_ho() ) return true;
		else if( a.get_ho() > b.get_ho() ) return false;
		else return false;
	}
}

bool the_loai_tang_dan(DS a, DS b ){
	if( a.get_the_loai() < b.get_the_loai() ) return true;
	else if( a.get_the_loai() > b.get_the_loai() ) return false;
	else{
		if( a.get_ten_sach() < b.get_ten_sach() ) return true;
		else if( a.get_ten_sach() > b.get_ten_sach() ) return false;
		else return false;
	}
}

bool qua_han_giam_dan(DG a, DG b){
	int max_a = 0, max_b = 0;
	N<MT>* dau = a.get_muon_tra().get_head();
	while(dau){
		if( dau->get_data().get_trang_thai() == 0 ){
			time_t baygio = time(0);
			tm *ltm = localtime(&baygio);
			NgayThang ngay_hien_tai(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
			int khoang_cach = ngay_hien_tai.kc_giua_2_ngay(dau->get_data().get_ngay_muon() );
			if( khoang_cach > 7 ){
				if( khoang_cach > max_a ) max_a = khoang_cach;
			}
		}
		dau = dau->get_next();
	}
	dau = b.get_muon_tra().get_head();
	while(dau){
		if( dau->get_data().get_trang_thai() == 0 ){
			time_t baygio = time(0);
			tm *ltm = localtime(&baygio);
			NgayThang ngay_hien_tai(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
			int khoang_cach = ngay_hien_tai.kc_giua_2_ngay(dau->get_data().get_ngay_muon() );
			if( khoang_cach > 7 ){
				if( khoang_cach > max_b ) max_b = khoang_cach;
			}
		}
		dau = dau->get_next();
	}
	if( max_a > max_b ) return true;
	return false;
}

bool muon_giam_dan(DS a, DS b){
	int count_a = 0, count_b = 0;
	Nut<DMS>* p = a.get_danh_muc_sach().get_head();
	while(p){
		if( p->get_data().get_trang_thai() == 1 ) count_a++;
		p = p->get_next();
	}
	p = b.get_danh_muc_sach().get_head();
	while(p){
		if( p->get_data().get_trang_thai() == 1 ) count_b++;
		p = p->get_next();
	}
	return count_a > count_b;
}

int main(){
	DauSach dau_sach;
	DocGia doc_gia;
	dau_sach.doc_file();
	doc_gia.doc_file();

	initwindow(1590, 820);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    gioi_thieu();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

    ControlCell ArrControlCell[20];
    initArrControlCell(ArrControlCell);
    int ma_tran[20][20];
    initMatran(ma_tran);

	const int DELAY = 100;
    bool back = false;
    bool end = false;
    while(true){
        menu(ArrControlCell);
        if(ismouseclick(WM_LBUTTONDOWN)){
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            for(int i = 0; i < 1; i++){
                if(clickControlCell(x, y, ArrControlCell[QUANLYDG])){
                    while(true){
                        menu(ArrControlCell);
                        childControlCell(ArrControlCell[QUANLYDG], ma_tran, ArrControlCell);
                        if(ismouseclick(WM_LBUTTONDOWN)){
                            getmouseclick(WM_LBUTTONDOWN, x, y);
                            for(int i = 0; i < 1; i++){
								if(clickControlCell(x, y, ArrControlCell[CAPNHATDG])){
						            while(true){
						                menu(ArrControlCell);
						                childControlCell(ArrControlCell[QUANLYDG], ma_tran, ArrControlCell);
						                childControlCell(ArrControlCell[CAPNHATDG], ma_tran, ArrControlCell);
						                if(ismouseclick(WM_LBUTTONDOWN)){
						                    getmouseclick(WM_LBUTTONDOWN, x, y);
						                    for(int i = 0; i < 1; i++){
												if(clickControlCell(x, y, ArrControlCell[THEMDG])){
											       //outtextxy(100, 600, "THEM DOC GIA");
											       doc_gia.them_doc_gia();
											    }
											    else if(clickControlCell(x, y, ArrControlCell[XOADG])){
											        //outtextxy(100, 700, "XOA DOC GIA");
											        doc_gia.xoa_doc_gia();
											    }
											    else if(clickControlCell(x, y, ArrControlCell[SUADG])){
											        //outtextxy(100, 750, "SUA DOC GIA");
											        doc_gia.sua_doc_gia();
											    }
											    else if(clickControlCell(x, y, ArrControlCell[XEMDG])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[MUONS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[TRAS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[SDANGMUON])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[MUONQUAHAN])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[QUANLYDG])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[QUANLYDS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												if(back){
													back = false;
													i--;
												}
											}
						                }
						                if( end ){
				                        	end = false;
				                        	break;
										}
										delay(DELAY);
						            }
						        }
						        else if(clickControlCell(x, y, ArrControlCell[XEMDG])){
						            while(true){
						                menu(ArrControlCell);
						                childControlCell(ArrControlCell[QUANLYDG], ma_tran, ArrControlCell);
						                childControlCell(ArrControlCell[XEMDG], ma_tran, ArrControlCell);
						                if(ismouseclick(WM_LBUTTONDOWN)){
						                    getmouseclick(WM_LBUTTONDOWN, x, y);
						                    for(int i = 0; i < 1; i++){
												if(clickControlCell(x, y, ArrControlCell[MATHETD])){
											        //outtextxy(500, 200, "MA THE TANG DAN");
											        doc_gia.in_td_theo_ma_dg();
											    }
											    else if(clickControlCell(x, y, ArrControlCell[HOTENTD])){
											        //outtextxy(500, 300, "HO TEN TANG DAN");
											        doc_gia.in_td_theo_ho_ten(ten_ho_tang_dan);
											    }
											    else if(clickControlCell(x, y, ArrControlCell[CAPNHATDG])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[MUONS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[TRAS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[SDANGMUON])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[MUONQUAHAN])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[QUANLYDG])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[QUANLYDS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
											    if(back){
													back = false;
													i--;
												}
											}
						                }
						                if( end ){
				                        	end = false;
				                        	break;
										}
										delay(DELAY);
						            }
						        }
						        else if(clickControlCell(x, y, ArrControlCell[MUONS])){
                                    doc_gia.muon_sach(dau_sach);
						        }
						        else if(clickControlCell(x, y, ArrControlCell[TRAS])){
                                    doc_gia.tra_sach(dau_sach);
						        }
						        else if(clickControlCell(x, y, ArrControlCell[SDANGMUON])){
                                    doc_gia.xem_sach_dang_muon(dau_sach);
						        }
						        else if(clickControlCell(x, y, ArrControlCell[MUONQUAHAN])){
                                    doc_gia.in_cac_doc_gia_muon_sach_qua_han_giam_dan(qua_han_giam_dan);
						        }
								else if(clickControlCell(x, y, ArrControlCell[QUANLYDS])){
									back = true;
									end = true;
									cleardevice();
									break;
								}
								if(back){
									back = false;
									i--;
								}
							}
                        }
                        if( end ){
                        	end = false;
                        	break;
						}
						delay(DELAY);
                    }
                }
                else if(clickControlCell(x, y, ArrControlCell[QUANLYDS])){
                    while(true){
                        menu(ArrControlCell);
                        childControlCell(ArrControlCell[QUANLYDS], ma_tran, ArrControlCell);
                        if(ismouseclick(WM_LBUTTONDOWN)){
                            getmouseclick(WM_LBUTTONDOWN, x, y);
                            for(int i = 0; i < 1; i++){
								if(clickControlCell(x, y, ArrControlCell[CAPNHATDS])){
						            while(true){
						                menu(ArrControlCell);
						                childControlCell(ArrControlCell[QUANLYDS], ma_tran, ArrControlCell);
						                childControlCell(ArrControlCell[CAPNHATDS], ma_tran, ArrControlCell);
						                if(ismouseclick(WM_LBUTTONDOWN)){
						                    getmouseclick(WM_LBUTTONDOWN, x, y);
						                    for(int i = 0; i < 1; i++){
												if(clickControlCell(x, y, ArrControlCell[THEMDS])){
											        //outtextxy(700, 300, "THEM DAU SACH");
											        dau_sach.them_dau_sach();
											    }
											    else if(clickControlCell(x, y, ArrControlCell[XOADS])){
											        //outtextxy(700, 400, "XOA DAU SACH");
											        dau_sach.xoa_dau_sach();
											    }
											    else if(clickControlCell(x, y, ArrControlCell[SUADS])){
											        //outtextxy(700, 500, "SUA DAU SACH");
											        dau_sach.sua_dau_sach();
											    }
											    else if(clickControlCell(x, y, ArrControlCell[XEMDS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[TIMS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[MUONNHIEUNHAT])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[QUANLYDG])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
												else if(clickControlCell(x, y, ArrControlCell[QUANLYDS])){
											    	back = true;
													end = true;
													cleardevice();
													break;
												}
											    if(back){
													back = false;
													i--;
												}
											}
						                }
						                if( end ){
				                        	end = false;
				                        	break;
										}
										delay(DELAY);
						            }

						        }
						        else if(clickControlCell(x, y, ArrControlCell[XEMDS])){
                                    dau_sach.in_td_theo_the_loai(the_loai_tang_dan);
						        }
						        else if(clickControlCell(x, y, ArrControlCell[TIMS])){
                                    dau_sach.tim_sach();
						        }
						        else if(clickControlCell(x, y, ArrControlCell[MUONNHIEUNHAT])){
                                    dau_sach.in_10_dau_sach_muon_nhieu_nhat(muon_giam_dan);
						        }
								else if(clickControlCell(x, y, ArrControlCell[QUANLYDG])){
							    	back = true;
									end = true;
									cleardevice();
									break;
								}
								if(back){
									back = false;
									i--;
								}
							}
                        }
                        if( end ){
                        	end = false;
                        	break;
						}
						delay(DELAY);
                    }
            	}
                if(back){
                    back = false;
                    i--;
                }
            }
        }
        delay(DELAY);
    }

	return 0;
}
