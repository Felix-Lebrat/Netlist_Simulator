#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <ctime>
#include <cmath>
#include <ncurses.h>

using namespace std;

bool get_bit(char *mem,int no);

void set_bit(char *mem,int no,bool val);

void copy(char *src,char *dest,int src_addr,int dest_addr,int word_size);

void create_mem(char **mem,int addr_size,int word_size);

int to_int(char *mem,int addr,int word_size);

void of_int(char *mem,int addr,int word_size,int i);

void print(char *mem,int addr,int word_size,bool meta);

bool of_input(char *mem,int size,string mem_name);

void of_string(char *mem,int size,string str);

void init_rom(char *rom,char* filename,bool hexa,int addr_size,int word_size);

void op_not(char *left,char* right,int size);

void op_and(char *left,char* a,char* b,int size);

void op_nand(char *left,char* a,char* b,int size);

void op_or(char *left,char* a,char* b,int size);

void op_xor(char *left,char* a,char* b,int size);

void op_concat(char *left,char* a,char* b,int a_size,int b_size);

void op_select(char *left,int i,char *a);

void op_mux(char* left,char* choice,char *a,char *b,int size);

void op_slice(char* left,int i1,int i2,char *a);

//l'horloge
struct Coord
{
        Coord():x(0),y(0){};
        Coord(double x,double y):x(x),y(y){};

        double x;
        double y;
};

Coord operator+(Coord const& a,Coord const& b);
Coord operator-(Coord const& a,Coord const& b);
Coord operator*(double const& a,Coord const& b);

void setPixel(Coord pos);

void segment(Coord a,Coord b);

const Coord segments[7][2]=
{
    {Coord(0,1),Coord(0,4)},
    {Coord(1,5),Coord(4,5)},
    {Coord(6,5),Coord(9,5)},
    {Coord(10,4),Coord(10,1)},
    {Coord(9,0),Coord(6,0)},
    {Coord(4,0),Coord(1,0)},
    {Coord(5,1),Coord(5,4)}
};

void afficheur(Coord pos,char val);

void horloge(Coord pos,char* data);

//déclaration des variables
char* fe_MUX51_reg;
char* fe_ROM0_rom;
char* _my_constant_2__reg;
char* fe_MUX5_reg;
char* fe_MUX6_reg;
char* fe_MUX9_reg;
char* fe_MUX10_reg;
char* fe_MUX15_reg;
char* fe_MUX16_reg;
char* fe_MUX19_reg;
char* fe_MUX20_reg;
char* fe_MUX27_reg;
char* fe_MUX28_reg;
char* fe_MUX31_reg;
char* fe_MUX32_reg;
char* fe_MUX37_reg;
char* fe_MUX38_reg;
char* fe_MUX41_reg;
char* fe_MUX42_reg;
char* fe_RAM0_ram;
char* _my_constant_0__mem;
bool _my_constant_0__bool;
function<char*()> _my_constant_0__fun;
char* _my_constant_1__mem;
bool _my_constant_1__bool;
function<char*()> _my_constant_1__fun;
char* _my_constant_2__mem;
bool _my_constant_2__bool;
function<char*()> _my_constant_2__fun;
char* _my_constant_3__mem;
bool _my_constant_3__bool;
function<char*()> _my_constant_3__fun;
char* _my_constant_4__mem;
bool _my_constant_4__bool;
function<char*()> _my_constant_4__fun;
char* fe_0_mem;
bool fe_0_bool;
function<char*()> fe_0_fun;
char* fe_AND0_mem;
bool fe_AND0_bool;
function<char*()> fe_AND0_fun;
char* fe_AND1_mem;
bool fe_AND1_bool;
function<char*()> fe_AND1_fun;
char* fe_AND10_mem;
bool fe_AND10_bool;
function<char*()> fe_AND10_fun;
char* fe_AND11_mem;
bool fe_AND11_bool;
function<char*()> fe_AND11_fun;
char* fe_AND12_mem;
bool fe_AND12_bool;
function<char*()> fe_AND12_fun;
char* fe_AND13_mem;
bool fe_AND13_bool;
function<char*()> fe_AND13_fun;
char* fe_AND14_mem;
bool fe_AND14_bool;
function<char*()> fe_AND14_fun;
char* fe_AND15_mem;
bool fe_AND15_bool;
function<char*()> fe_AND15_fun;
char* fe_AND16_mem;
bool fe_AND16_bool;
function<char*()> fe_AND16_fun;
char* fe_AND17_mem;
bool fe_AND17_bool;
function<char*()> fe_AND17_fun;
char* fe_AND18_mem;
bool fe_AND18_bool;
function<char*()> fe_AND18_fun;
char* fe_AND19_mem;
bool fe_AND19_bool;
function<char*()> fe_AND19_fun;
char* fe_AND2_mem;
bool fe_AND2_bool;
function<char*()> fe_AND2_fun;
char* fe_AND20_mem;
bool fe_AND20_bool;
function<char*()> fe_AND20_fun;
char* fe_AND21_mem;
bool fe_AND21_bool;
function<char*()> fe_AND21_fun;
char* fe_AND22_mem;
bool fe_AND22_bool;
function<char*()> fe_AND22_fun;
char* fe_AND23_mem;
bool fe_AND23_bool;
function<char*()> fe_AND23_fun;
char* fe_AND24_mem;
bool fe_AND24_bool;
function<char*()> fe_AND24_fun;
char* fe_AND25_mem;
bool fe_AND25_bool;
function<char*()> fe_AND25_fun;
char* fe_AND26_mem;
bool fe_AND26_bool;
function<char*()> fe_AND26_fun;
char* fe_AND27_mem;
bool fe_AND27_bool;
function<char*()> fe_AND27_fun;
char* fe_AND28_mem;
bool fe_AND28_bool;
function<char*()> fe_AND28_fun;
char* fe_AND29_mem;
bool fe_AND29_bool;
function<char*()> fe_AND29_fun;
char* fe_AND3_mem;
bool fe_AND3_bool;
function<char*()> fe_AND3_fun;
char* fe_AND30_mem;
bool fe_AND30_bool;
function<char*()> fe_AND30_fun;
char* fe_AND31_mem;
bool fe_AND31_bool;
function<char*()> fe_AND31_fun;
char* fe_AND32_mem;
bool fe_AND32_bool;
function<char*()> fe_AND32_fun;
char* fe_AND33_mem;
bool fe_AND33_bool;
function<char*()> fe_AND33_fun;
char* fe_AND34_mem;
bool fe_AND34_bool;
function<char*()> fe_AND34_fun;
char* fe_AND35_mem;
bool fe_AND35_bool;
function<char*()> fe_AND35_fun;
char* fe_AND36_mem;
bool fe_AND36_bool;
function<char*()> fe_AND36_fun;
char* fe_AND37_mem;
bool fe_AND37_bool;
function<char*()> fe_AND37_fun;
char* fe_AND38_mem;
bool fe_AND38_bool;
function<char*()> fe_AND38_fun;
char* fe_AND39_mem;
bool fe_AND39_bool;
function<char*()> fe_AND39_fun;
char* fe_AND4_mem;
bool fe_AND4_bool;
function<char*()> fe_AND4_fun;
char* fe_AND40_mem;
bool fe_AND40_bool;
function<char*()> fe_AND40_fun;
char* fe_AND41_mem;
bool fe_AND41_bool;
function<char*()> fe_AND41_fun;
char* fe_AND42_mem;
bool fe_AND42_bool;
function<char*()> fe_AND42_fun;
char* fe_AND43_mem;
bool fe_AND43_bool;
function<char*()> fe_AND43_fun;
char* fe_AND44_mem;
bool fe_AND44_bool;
function<char*()> fe_AND44_fun;
char* fe_AND45_mem;
bool fe_AND45_bool;
function<char*()> fe_AND45_fun;
char* fe_AND46_mem;
bool fe_AND46_bool;
function<char*()> fe_AND46_fun;
char* fe_AND47_mem;
bool fe_AND47_bool;
function<char*()> fe_AND47_fun;
char* fe_AND48_mem;
bool fe_AND48_bool;
function<char*()> fe_AND48_fun;
char* fe_AND49_mem;
bool fe_AND49_bool;
function<char*()> fe_AND49_fun;
char* fe_AND5_mem;
bool fe_AND5_bool;
function<char*()> fe_AND5_fun;
char* fe_AND50_mem;
bool fe_AND50_bool;
function<char*()> fe_AND50_fun;
char* fe_AND51_mem;
bool fe_AND51_bool;
function<char*()> fe_AND51_fun;
char* fe_AND52_mem;
bool fe_AND52_bool;
function<char*()> fe_AND52_fun;
char* fe_AND53_mem;
bool fe_AND53_bool;
function<char*()> fe_AND53_fun;
char* fe_AND54_mem;
bool fe_AND54_bool;
function<char*()> fe_AND54_fun;
char* fe_AND55_mem;
bool fe_AND55_bool;
function<char*()> fe_AND55_fun;
char* fe_AND56_mem;
bool fe_AND56_bool;
function<char*()> fe_AND56_fun;
char* fe_AND57_mem;
bool fe_AND57_bool;
function<char*()> fe_AND57_fun;
char* fe_AND58_mem;
bool fe_AND58_bool;
function<char*()> fe_AND58_fun;
char* fe_AND59_mem;
bool fe_AND59_bool;
function<char*()> fe_AND59_fun;
char* fe_AND6_mem;
bool fe_AND6_bool;
function<char*()> fe_AND6_fun;
char* fe_AND60_mem;
bool fe_AND60_bool;
function<char*()> fe_AND60_fun;
char* fe_AND61_mem;
bool fe_AND61_bool;
function<char*()> fe_AND61_fun;
char* fe_AND62_mem;
bool fe_AND62_bool;
function<char*()> fe_AND62_fun;
char* fe_AND63_mem;
bool fe_AND63_bool;
function<char*()> fe_AND63_fun;
char* fe_AND64_mem;
bool fe_AND64_bool;
function<char*()> fe_AND64_fun;
char* fe_AND65_mem;
bool fe_AND65_bool;
function<char*()> fe_AND65_fun;
char* fe_AND66_mem;
bool fe_AND66_bool;
function<char*()> fe_AND66_fun;
char* fe_AND67_mem;
bool fe_AND67_bool;
function<char*()> fe_AND67_fun;
char* fe_AND68_mem;
bool fe_AND68_bool;
function<char*()> fe_AND68_fun;
char* fe_AND69_mem;
bool fe_AND69_bool;
function<char*()> fe_AND69_fun;
char* fe_AND7_mem;
bool fe_AND7_bool;
function<char*()> fe_AND7_fun;
char* fe_AND70_mem;
bool fe_AND70_bool;
function<char*()> fe_AND70_fun;
char* fe_AND71_mem;
bool fe_AND71_bool;
function<char*()> fe_AND71_fun;
char* fe_AND72_mem;
bool fe_AND72_bool;
function<char*()> fe_AND72_fun;
char* fe_AND73_mem;
bool fe_AND73_bool;
function<char*()> fe_AND73_fun;
char* fe_AND74_mem;
bool fe_AND74_bool;
function<char*()> fe_AND74_fun;
char* fe_AND75_mem;
bool fe_AND75_bool;
function<char*()> fe_AND75_fun;
char* fe_AND76_mem;
bool fe_AND76_bool;
function<char*()> fe_AND76_fun;
char* fe_AND77_mem;
bool fe_AND77_bool;
function<char*()> fe_AND77_fun;
char* fe_AND78_mem;
bool fe_AND78_bool;
function<char*()> fe_AND78_fun;
char* fe_AND8_mem;
bool fe_AND8_bool;
function<char*()> fe_AND8_fun;
char* fe_AND9_mem;
bool fe_AND9_bool;
function<char*()> fe_AND9_fun;
char* fe_CONCAT0_mem;
bool fe_CONCAT0_bool;
function<char*()> fe_CONCAT0_fun;
char* fe_CONCAT1_mem;
bool fe_CONCAT1_bool;
function<char*()> fe_CONCAT1_fun;
char* fe_CONCAT10_mem;
bool fe_CONCAT10_bool;
function<char*()> fe_CONCAT10_fun;
char* fe_CONCAT11_mem;
bool fe_CONCAT11_bool;
function<char*()> fe_CONCAT11_fun;
char* fe_CONCAT12_mem;
bool fe_CONCAT12_bool;
function<char*()> fe_CONCAT12_fun;
char* fe_CONCAT13_mem;
bool fe_CONCAT13_bool;
function<char*()> fe_CONCAT13_fun;
char* fe_CONCAT14_mem;
bool fe_CONCAT14_bool;
function<char*()> fe_CONCAT14_fun;
char* fe_CONCAT15_mem;
bool fe_CONCAT15_bool;
function<char*()> fe_CONCAT15_fun;
char* fe_CONCAT16_mem;
bool fe_CONCAT16_bool;
function<char*()> fe_CONCAT16_fun;
char* fe_CONCAT17_mem;
bool fe_CONCAT17_bool;
function<char*()> fe_CONCAT17_fun;
char* fe_CONCAT18_mem;
bool fe_CONCAT18_bool;
function<char*()> fe_CONCAT18_fun;
char* fe_CONCAT19_mem;
bool fe_CONCAT19_bool;
function<char*()> fe_CONCAT19_fun;
char* fe_CONCAT2_mem;
bool fe_CONCAT2_bool;
function<char*()> fe_CONCAT2_fun;
char* fe_CONCAT3_mem;
bool fe_CONCAT3_bool;
function<char*()> fe_CONCAT3_fun;
char* fe_CONCAT4_mem;
bool fe_CONCAT4_bool;
function<char*()> fe_CONCAT4_fun;
char* fe_CONCAT5_mem;
bool fe_CONCAT5_bool;
function<char*()> fe_CONCAT5_fun;
char* fe_CONCAT6_mem;
bool fe_CONCAT6_bool;
function<char*()> fe_CONCAT6_fun;
char* fe_CONCAT7_mem;
bool fe_CONCAT7_bool;
function<char*()> fe_CONCAT7_fun;
char* fe_CONCAT8_mem;
bool fe_CONCAT8_bool;
function<char*()> fe_CONCAT8_fun;
char* fe_CONCAT9_mem;
bool fe_CONCAT9_bool;
function<char*()> fe_CONCAT9_fun;
char* fe_MUX0_mem;
bool fe_MUX0_bool;
function<char*()> fe_MUX0_fun;
char* fe_MUX1_mem;
bool fe_MUX1_bool;
function<char*()> fe_MUX1_fun;
char* fe_MUX10_mem;
bool fe_MUX10_bool;
function<char*()> fe_MUX10_fun;
char* fe_MUX11_mem;
bool fe_MUX11_bool;
function<char*()> fe_MUX11_fun;
char* fe_MUX12_mem;
bool fe_MUX12_bool;
function<char*()> fe_MUX12_fun;
char* fe_MUX13_mem;
bool fe_MUX13_bool;
function<char*()> fe_MUX13_fun;
char* fe_MUX14_mem;
bool fe_MUX14_bool;
function<char*()> fe_MUX14_fun;
char* fe_MUX15_mem;
bool fe_MUX15_bool;
function<char*()> fe_MUX15_fun;
char* fe_MUX16_mem;
bool fe_MUX16_bool;
function<char*()> fe_MUX16_fun;
char* fe_MUX17_mem;
bool fe_MUX17_bool;
function<char*()> fe_MUX17_fun;
char* fe_MUX18_mem;
bool fe_MUX18_bool;
function<char*()> fe_MUX18_fun;
char* fe_MUX19_mem;
bool fe_MUX19_bool;
function<char*()> fe_MUX19_fun;
char* fe_MUX2_mem;
bool fe_MUX2_bool;
function<char*()> fe_MUX2_fun;
char* fe_MUX20_mem;
bool fe_MUX20_bool;
function<char*()> fe_MUX20_fun;
char* fe_MUX21_mem;
bool fe_MUX21_bool;
function<char*()> fe_MUX21_fun;
char* fe_MUX22_mem;
bool fe_MUX22_bool;
function<char*()> fe_MUX22_fun;
char* fe_MUX23_mem;
bool fe_MUX23_bool;
function<char*()> fe_MUX23_fun;
char* fe_MUX24_mem;
bool fe_MUX24_bool;
function<char*()> fe_MUX24_fun;
char* fe_MUX25_mem;
bool fe_MUX25_bool;
function<char*()> fe_MUX25_fun;
char* fe_MUX26_mem;
bool fe_MUX26_bool;
function<char*()> fe_MUX26_fun;
char* fe_MUX27_mem;
bool fe_MUX27_bool;
function<char*()> fe_MUX27_fun;
char* fe_MUX28_mem;
bool fe_MUX28_bool;
function<char*()> fe_MUX28_fun;
char* fe_MUX29_mem;
bool fe_MUX29_bool;
function<char*()> fe_MUX29_fun;
char* fe_MUX3_mem;
bool fe_MUX3_bool;
function<char*()> fe_MUX3_fun;
char* fe_MUX30_mem;
bool fe_MUX30_bool;
function<char*()> fe_MUX30_fun;
char* fe_MUX31_mem;
bool fe_MUX31_bool;
function<char*()> fe_MUX31_fun;
char* fe_MUX32_mem;
bool fe_MUX32_bool;
function<char*()> fe_MUX32_fun;
char* fe_MUX33_mem;
bool fe_MUX33_bool;
function<char*()> fe_MUX33_fun;
char* fe_MUX34_mem;
bool fe_MUX34_bool;
function<char*()> fe_MUX34_fun;
char* fe_MUX35_mem;
bool fe_MUX35_bool;
function<char*()> fe_MUX35_fun;
char* fe_MUX36_mem;
bool fe_MUX36_bool;
function<char*()> fe_MUX36_fun;
char* fe_MUX37_mem;
bool fe_MUX37_bool;
function<char*()> fe_MUX37_fun;
char* fe_MUX38_mem;
bool fe_MUX38_bool;
function<char*()> fe_MUX38_fun;
char* fe_MUX39_mem;
bool fe_MUX39_bool;
function<char*()> fe_MUX39_fun;
char* fe_MUX4_mem;
bool fe_MUX4_bool;
function<char*()> fe_MUX4_fun;
char* fe_MUX40_mem;
bool fe_MUX40_bool;
function<char*()> fe_MUX40_fun;
char* fe_MUX41_mem;
bool fe_MUX41_bool;
function<char*()> fe_MUX41_fun;
char* fe_MUX42_mem;
bool fe_MUX42_bool;
function<char*()> fe_MUX42_fun;
char* fe_MUX43_mem;
bool fe_MUX43_bool;
function<char*()> fe_MUX43_fun;
char* fe_MUX44_mem;
bool fe_MUX44_bool;
function<char*()> fe_MUX44_fun;
char* fe_MUX45_mem;
bool fe_MUX45_bool;
function<char*()> fe_MUX45_fun;
char* fe_MUX46_mem;
bool fe_MUX46_bool;
function<char*()> fe_MUX46_fun;
char* fe_MUX47_mem;
bool fe_MUX47_bool;
function<char*()> fe_MUX47_fun;
char* fe_MUX48_mem;
bool fe_MUX48_bool;
function<char*()> fe_MUX48_fun;
char* fe_MUX49_mem;
bool fe_MUX49_bool;
function<char*()> fe_MUX49_fun;
char* fe_MUX5_mem;
bool fe_MUX5_bool;
function<char*()> fe_MUX5_fun;
char* fe_MUX50_mem;
bool fe_MUX50_bool;
function<char*()> fe_MUX50_fun;
char* fe_MUX51_mem;
bool fe_MUX51_bool;
function<char*()> fe_MUX51_fun;
char* fe_MUX6_mem;
bool fe_MUX6_bool;
function<char*()> fe_MUX6_fun;
char* fe_MUX7_mem;
bool fe_MUX7_bool;
function<char*()> fe_MUX7_fun;
char* fe_MUX8_mem;
bool fe_MUX8_bool;
function<char*()> fe_MUX8_fun;
char* fe_MUX9_mem;
bool fe_MUX9_bool;
function<char*()> fe_MUX9_fun;
char* fe_NOT0_mem;
bool fe_NOT0_bool;
function<char*()> fe_NOT0_fun;
char* fe_NOT1_mem;
bool fe_NOT1_bool;
function<char*()> fe_NOT1_fun;
char* fe_NOT10_mem;
bool fe_NOT10_bool;
function<char*()> fe_NOT10_fun;
char* fe_NOT11_mem;
bool fe_NOT11_bool;
function<char*()> fe_NOT11_fun;
char* fe_NOT12_mem;
bool fe_NOT12_bool;
function<char*()> fe_NOT12_fun;
char* fe_NOT13_mem;
bool fe_NOT13_bool;
function<char*()> fe_NOT13_fun;
char* fe_NOT14_mem;
bool fe_NOT14_bool;
function<char*()> fe_NOT14_fun;
char* fe_NOT15_mem;
bool fe_NOT15_bool;
function<char*()> fe_NOT15_fun;
char* fe_NOT16_mem;
bool fe_NOT16_bool;
function<char*()> fe_NOT16_fun;
char* fe_NOT17_mem;
bool fe_NOT17_bool;
function<char*()> fe_NOT17_fun;
char* fe_NOT18_mem;
bool fe_NOT18_bool;
function<char*()> fe_NOT18_fun;
char* fe_NOT19_mem;
bool fe_NOT19_bool;
function<char*()> fe_NOT19_fun;
char* fe_NOT2_mem;
bool fe_NOT2_bool;
function<char*()> fe_NOT2_fun;
char* fe_NOT20_mem;
bool fe_NOT20_bool;
function<char*()> fe_NOT20_fun;
char* fe_NOT21_mem;
bool fe_NOT21_bool;
function<char*()> fe_NOT21_fun;
char* fe_NOT22_mem;
bool fe_NOT22_bool;
function<char*()> fe_NOT22_fun;
char* fe_NOT3_mem;
bool fe_NOT3_bool;
function<char*()> fe_NOT3_fun;
char* fe_NOT4_mem;
bool fe_NOT4_bool;
function<char*()> fe_NOT4_fun;
char* fe_NOT5_mem;
bool fe_NOT5_bool;
function<char*()> fe_NOT5_fun;
char* fe_NOT6_mem;
bool fe_NOT6_bool;
function<char*()> fe_NOT6_fun;
char* fe_NOT7_mem;
bool fe_NOT7_bool;
function<char*()> fe_NOT7_fun;
char* fe_NOT8_mem;
bool fe_NOT8_bool;
function<char*()> fe_NOT8_fun;
char* fe_NOT9_mem;
bool fe_NOT9_bool;
function<char*()> fe_NOT9_fun;
char* fe_OR0_mem;
bool fe_OR0_bool;
function<char*()> fe_OR0_fun;
char* fe_OR1_mem;
bool fe_OR1_bool;
function<char*()> fe_OR1_fun;
char* fe_OR10_mem;
bool fe_OR10_bool;
function<char*()> fe_OR10_fun;
char* fe_OR11_mem;
bool fe_OR11_bool;
function<char*()> fe_OR11_fun;
char* fe_OR2_mem;
bool fe_OR2_bool;
function<char*()> fe_OR2_fun;
char* fe_OR3_mem;
bool fe_OR3_bool;
function<char*()> fe_OR3_fun;
char* fe_OR4_mem;
bool fe_OR4_bool;
function<char*()> fe_OR4_fun;
char* fe_OR5_mem;
bool fe_OR5_bool;
function<char*()> fe_OR5_fun;
char* fe_OR6_mem;
bool fe_OR6_bool;
function<char*()> fe_OR6_fun;
char* fe_OR7_mem;
bool fe_OR7_bool;
function<char*()> fe_OR7_fun;
char* fe_OR8_mem;
bool fe_OR8_bool;
function<char*()> fe_OR8_fun;
char* fe_OR9_mem;
bool fe_OR9_bool;
function<char*()> fe_OR9_fun;
char* fe_RAM0_mem;
bool fe_RAM0_bool;
function<char*()> fe_RAM0_fun;
char* fe_REG0_mem;
bool fe_REG0_bool;
function<char*()> fe_REG0_fun;
char* fe_REG1_mem;
bool fe_REG1_bool;
function<char*()> fe_REG1_fun;
char* fe_REG10_mem;
bool fe_REG10_bool;
function<char*()> fe_REG10_fun;
char* fe_REG11_mem;
bool fe_REG11_bool;
function<char*()> fe_REG11_fun;
char* fe_REG12_mem;
bool fe_REG12_bool;
function<char*()> fe_REG12_fun;
char* fe_REG13_mem;
bool fe_REG13_bool;
function<char*()> fe_REG13_fun;
char* fe_REG14_mem;
bool fe_REG14_bool;
function<char*()> fe_REG14_fun;
char* fe_REG15_mem;
bool fe_REG15_bool;
function<char*()> fe_REG15_fun;
char* fe_REG16_mem;
bool fe_REG16_bool;
function<char*()> fe_REG16_fun;
char* fe_REG17_mem;
bool fe_REG17_bool;
function<char*()> fe_REG17_fun;
char* fe_REG2_mem;
bool fe_REG2_bool;
function<char*()> fe_REG2_fun;
char* fe_REG3_mem;
bool fe_REG3_bool;
function<char*()> fe_REG3_fun;
char* fe_REG4_mem;
bool fe_REG4_bool;
function<char*()> fe_REG4_fun;
char* fe_REG5_mem;
bool fe_REG5_bool;
function<char*()> fe_REG5_fun;
char* fe_REG6_mem;
bool fe_REG6_bool;
function<char*()> fe_REG6_fun;
char* fe_REG7_mem;
bool fe_REG7_bool;
function<char*()> fe_REG7_fun;
char* fe_REG8_mem;
bool fe_REG8_bool;
function<char*()> fe_REG8_fun;
char* fe_REG9_mem;
bool fe_REG9_bool;
function<char*()> fe_REG9_fun;
char* fe_ROM0_mem;
bool fe_ROM0_bool;
function<char*()> fe_ROM0_fun;
char* fe_SELECT0_mem;
bool fe_SELECT0_bool;
function<char*()> fe_SELECT0_fun;
char* fe_SELECT1_mem;
bool fe_SELECT1_bool;
function<char*()> fe_SELECT1_fun;
char* fe_SELECT10_mem;
bool fe_SELECT10_bool;
function<char*()> fe_SELECT10_fun;
char* fe_SELECT11_mem;
bool fe_SELECT11_bool;
function<char*()> fe_SELECT11_fun;
char* fe_SELECT12_mem;
bool fe_SELECT12_bool;
function<char*()> fe_SELECT12_fun;
char* fe_SELECT13_mem;
bool fe_SELECT13_bool;
function<char*()> fe_SELECT13_fun;
char* fe_SELECT14_mem;
bool fe_SELECT14_bool;
function<char*()> fe_SELECT14_fun;
char* fe_SELECT15_mem;
bool fe_SELECT15_bool;
function<char*()> fe_SELECT15_fun;
char* fe_SELECT16_mem;
bool fe_SELECT16_bool;
function<char*()> fe_SELECT16_fun;
char* fe_SELECT17_mem;
bool fe_SELECT17_bool;
function<char*()> fe_SELECT17_fun;
char* fe_SELECT18_mem;
bool fe_SELECT18_bool;
function<char*()> fe_SELECT18_fun;
char* fe_SELECT19_mem;
bool fe_SELECT19_bool;
function<char*()> fe_SELECT19_fun;
char* fe_SELECT2_mem;
bool fe_SELECT2_bool;
function<char*()> fe_SELECT2_fun;
char* fe_SELECT20_mem;
bool fe_SELECT20_bool;
function<char*()> fe_SELECT20_fun;
char* fe_SELECT21_mem;
bool fe_SELECT21_bool;
function<char*()> fe_SELECT21_fun;
char* fe_SELECT22_mem;
bool fe_SELECT22_bool;
function<char*()> fe_SELECT22_fun;
char* fe_SELECT23_mem;
bool fe_SELECT23_bool;
function<char*()> fe_SELECT23_fun;
char* fe_SELECT24_mem;
bool fe_SELECT24_bool;
function<char*()> fe_SELECT24_fun;
char* fe_SELECT25_mem;
bool fe_SELECT25_bool;
function<char*()> fe_SELECT25_fun;
char* fe_SELECT26_mem;
bool fe_SELECT26_bool;
function<char*()> fe_SELECT26_fun;
char* fe_SELECT27_mem;
bool fe_SELECT27_bool;
function<char*()> fe_SELECT27_fun;
char* fe_SELECT28_mem;
bool fe_SELECT28_bool;
function<char*()> fe_SELECT28_fun;
char* fe_SELECT29_mem;
bool fe_SELECT29_bool;
function<char*()> fe_SELECT29_fun;
char* fe_SELECT3_mem;
bool fe_SELECT3_bool;
function<char*()> fe_SELECT3_fun;
char* fe_SELECT30_mem;
bool fe_SELECT30_bool;
function<char*()> fe_SELECT30_fun;
char* fe_SELECT31_mem;
bool fe_SELECT31_bool;
function<char*()> fe_SELECT31_fun;
char* fe_SELECT32_mem;
bool fe_SELECT32_bool;
function<char*()> fe_SELECT32_fun;
char* fe_SELECT33_mem;
bool fe_SELECT33_bool;
function<char*()> fe_SELECT33_fun;
char* fe_SELECT34_mem;
bool fe_SELECT34_bool;
function<char*()> fe_SELECT34_fun;
char* fe_SELECT35_mem;
bool fe_SELECT35_bool;
function<char*()> fe_SELECT35_fun;
char* fe_SELECT36_mem;
bool fe_SELECT36_bool;
function<char*()> fe_SELECT36_fun;
char* fe_SELECT37_mem;
bool fe_SELECT37_bool;
function<char*()> fe_SELECT37_fun;
char* fe_SELECT38_mem;
bool fe_SELECT38_bool;
function<char*()> fe_SELECT38_fun;
char* fe_SELECT39_mem;
bool fe_SELECT39_bool;
function<char*()> fe_SELECT39_fun;
char* fe_SELECT4_mem;
bool fe_SELECT4_bool;
function<char*()> fe_SELECT4_fun;
char* fe_SELECT40_mem;
bool fe_SELECT40_bool;
function<char*()> fe_SELECT40_fun;
char* fe_SELECT41_mem;
bool fe_SELECT41_bool;
function<char*()> fe_SELECT41_fun;
char* fe_SELECT42_mem;
bool fe_SELECT42_bool;
function<char*()> fe_SELECT42_fun;
char* fe_SELECT43_mem;
bool fe_SELECT43_bool;
function<char*()> fe_SELECT43_fun;
char* fe_SELECT44_mem;
bool fe_SELECT44_bool;
function<char*()> fe_SELECT44_fun;
char* fe_SELECT5_mem;
bool fe_SELECT5_bool;
function<char*()> fe_SELECT5_fun;
char* fe_SELECT6_mem;
bool fe_SELECT6_bool;
function<char*()> fe_SELECT6_fun;
char* fe_SELECT7_mem;
bool fe_SELECT7_bool;
function<char*()> fe_SELECT7_fun;
char* fe_SELECT8_mem;
bool fe_SELECT8_bool;
function<char*()> fe_SELECT8_fun;
char* fe_SELECT9_mem;
bool fe_SELECT9_bool;
function<char*()> fe_SELECT9_fun;
char* fe_SLICE0_mem;
bool fe_SLICE0_bool;
function<char*()> fe_SLICE0_fun;
char* fe_SLICE1_mem;
bool fe_SLICE1_bool;
function<char*()> fe_SLICE1_fun;
char* fe_SLICE10_mem;
bool fe_SLICE10_bool;
function<char*()> fe_SLICE10_fun;
char* fe_SLICE11_mem;
bool fe_SLICE11_bool;
function<char*()> fe_SLICE11_fun;
char* fe_SLICE12_mem;
bool fe_SLICE12_bool;
function<char*()> fe_SLICE12_fun;
char* fe_SLICE13_mem;
bool fe_SLICE13_bool;
function<char*()> fe_SLICE13_fun;
char* fe_SLICE14_mem;
bool fe_SLICE14_bool;
function<char*()> fe_SLICE14_fun;
char* fe_SLICE15_mem;
bool fe_SLICE15_bool;
function<char*()> fe_SLICE15_fun;
char* fe_SLICE2_mem;
bool fe_SLICE2_bool;
function<char*()> fe_SLICE2_fun;
char* fe_SLICE3_mem;
bool fe_SLICE3_bool;
function<char*()> fe_SLICE3_fun;
char* fe_SLICE4_mem;
bool fe_SLICE4_bool;
function<char*()> fe_SLICE4_fun;
char* fe_SLICE5_mem;
bool fe_SLICE5_bool;
function<char*()> fe_SLICE5_fun;
char* fe_SLICE6_mem;
bool fe_SLICE6_bool;
function<char*()> fe_SLICE6_fun;
char* fe_SLICE7_mem;
bool fe_SLICE7_bool;
function<char*()> fe_SLICE7_fun;
char* fe_SLICE8_mem;
bool fe_SLICE8_bool;
function<char*()> fe_SLICE8_fun;
char* fe_SLICE9_mem;
bool fe_SLICE9_bool;
function<char*()> fe_SLICE9_fun;
char* fe_XOR0_mem;
bool fe_XOR0_bool;
function<char*()> fe_XOR0_fun;
char* fe_XOR1_mem;
bool fe_XOR1_bool;
function<char*()> fe_XOR1_fun;
char* fe_XOR10_mem;
bool fe_XOR10_bool;
function<char*()> fe_XOR10_fun;
char* fe_XOR11_mem;
bool fe_XOR11_bool;
function<char*()> fe_XOR11_fun;
char* fe_XOR12_mem;
bool fe_XOR12_bool;
function<char*()> fe_XOR12_fun;
char* fe_XOR2_mem;
bool fe_XOR2_bool;
function<char*()> fe_XOR2_fun;
char* fe_XOR3_mem;
bool fe_XOR3_bool;
function<char*()> fe_XOR3_fun;
char* fe_XOR4_mem;
bool fe_XOR4_bool;
function<char*()> fe_XOR4_fun;
char* fe_XOR5_mem;
bool fe_XOR5_bool;
function<char*()> fe_XOR5_fun;
char* fe_XOR6_mem;
bool fe_XOR6_bool;
function<char*()> fe_XOR6_fun;
char* fe_XOR7_mem;
bool fe_XOR7_bool;
function<char*()> fe_XOR7_fun;
char* fe_XOR8_mem;
bool fe_XOR8_bool;
function<char*()> fe_XOR8_fun;
char* fe_XOR9_mem;
bool fe_XOR9_bool;
function<char*()> fe_XOR9_fun;


int main(int argc,char **argv)
{

    int step=-1;
    bool hexa=false;
    int clock=0;
    char clock_data[14];

    for(int i=1;i<argc;i++)
    {
        if(argv[i]==string("-h"))
        {
            hexa=true;
            continue;
        }
        if(argv[i]==string("-s"))
        {
            i++;
            if(i<argc)
            {
                step=atoi(argv[i]);
            }
            continue;
        }
    }

    //initialisation des roms
	create_mem(&fe_ROM0_rom,13,32);
	init_rom(fe_ROM0_rom,"fe_ROM0",hexa,13,32);


    //creation des rams
	create_mem(&fe_RAM0_ram,13,32);


    //creation des variables
	create_mem(&_my_constant_0__mem,0,19);
	create_mem(&_my_constant_1__mem,0,1);
	create_mem(&_my_constant_2__mem,0,2);
	create_mem(&_my_constant_3__mem,0,1);
	create_mem(&_my_constant_4__mem,0,1);
	create_mem(&fe_0_mem,0,32);
	create_mem(&fe_AND0_mem,0,1);
	create_mem(&fe_AND1_mem,0,1);
	create_mem(&fe_AND10_mem,0,1);
	create_mem(&fe_AND11_mem,0,1);
	create_mem(&fe_AND12_mem,0,1);
	create_mem(&fe_AND13_mem,0,1);
	create_mem(&fe_AND14_mem,0,1);
	create_mem(&fe_AND15_mem,0,1);
	create_mem(&fe_AND16_mem,0,1);
	create_mem(&fe_AND17_mem,0,1);
	create_mem(&fe_AND18_mem,0,1);
	create_mem(&fe_AND19_mem,0,1);
	create_mem(&fe_AND2_mem,0,1);
	create_mem(&fe_AND20_mem,0,1);
	create_mem(&fe_AND21_mem,0,1);
	create_mem(&fe_AND22_mem,0,1);
	create_mem(&fe_AND23_mem,0,1);
	create_mem(&fe_AND24_mem,0,1);
	create_mem(&fe_AND25_mem,0,1);
	create_mem(&fe_AND26_mem,0,1);
	create_mem(&fe_AND27_mem,0,1);
	create_mem(&fe_AND28_mem,0,1);
	create_mem(&fe_AND29_mem,0,1);
	create_mem(&fe_AND3_mem,0,1);
	create_mem(&fe_AND30_mem,0,1);
	create_mem(&fe_AND31_mem,0,1);
	create_mem(&fe_AND32_mem,0,1);
	create_mem(&fe_AND33_mem,0,1);
	create_mem(&fe_AND34_mem,0,1);
	create_mem(&fe_AND35_mem,0,1);
	create_mem(&fe_AND36_mem,0,1);
	create_mem(&fe_AND37_mem,0,1);
	create_mem(&fe_AND38_mem,0,1);
	create_mem(&fe_AND39_mem,0,1);
	create_mem(&fe_AND4_mem,0,1);
	create_mem(&fe_AND40_mem,0,1);
	create_mem(&fe_AND41_mem,0,1);
	create_mem(&fe_AND42_mem,0,1);
	create_mem(&fe_AND43_mem,0,1);
	create_mem(&fe_AND44_mem,0,1);
	create_mem(&fe_AND45_mem,0,1);
	create_mem(&fe_AND46_mem,0,1);
	create_mem(&fe_AND47_mem,0,1);
	create_mem(&fe_AND48_mem,0,1);
	create_mem(&fe_AND49_mem,0,1);
	create_mem(&fe_AND5_mem,0,1);
	create_mem(&fe_AND50_mem,0,1);
	create_mem(&fe_AND51_mem,0,1);
	create_mem(&fe_AND52_mem,0,1);
	create_mem(&fe_AND53_mem,0,1);
	create_mem(&fe_AND54_mem,0,1);
	create_mem(&fe_AND55_mem,0,1);
	create_mem(&fe_AND56_mem,0,1);
	create_mem(&fe_AND57_mem,0,1);
	create_mem(&fe_AND58_mem,0,1);
	create_mem(&fe_AND59_mem,0,1);
	create_mem(&fe_AND6_mem,0,1);
	create_mem(&fe_AND60_mem,0,1);
	create_mem(&fe_AND61_mem,0,1);
	create_mem(&fe_AND62_mem,0,1);
	create_mem(&fe_AND63_mem,0,1);
	create_mem(&fe_AND64_mem,0,1);
	create_mem(&fe_AND65_mem,0,1);
	create_mem(&fe_AND66_mem,0,1);
	create_mem(&fe_AND67_mem,0,1);
	create_mem(&fe_AND68_mem,0,1);
	create_mem(&fe_AND69_mem,0,1);
	create_mem(&fe_AND7_mem,0,1);
	create_mem(&fe_AND70_mem,0,1);
	create_mem(&fe_AND71_mem,0,1);
	create_mem(&fe_AND72_mem,0,1);
	create_mem(&fe_AND73_mem,0,1);
	create_mem(&fe_AND74_mem,0,1);
	create_mem(&fe_AND75_mem,0,1);
	create_mem(&fe_AND76_mem,0,1);
	create_mem(&fe_AND77_mem,0,1);
	create_mem(&fe_AND78_mem,0,1);
	create_mem(&fe_AND8_mem,0,1);
	create_mem(&fe_AND9_mem,0,1);
	create_mem(&fe_CONCAT0_mem,0,32);
	create_mem(&fe_CONCAT1_mem,0,2);
	create_mem(&fe_CONCAT10_mem,0,2);
	create_mem(&fe_CONCAT11_mem,0,3);
	create_mem(&fe_CONCAT12_mem,0,6);
	create_mem(&fe_CONCAT13_mem,0,2);
	create_mem(&fe_CONCAT14_mem,0,3);
	create_mem(&fe_CONCAT15_mem,0,2);
	create_mem(&fe_CONCAT16_mem,0,2);
	create_mem(&fe_CONCAT17_mem,0,4);
	create_mem(&fe_CONCAT18_mem,0,7);
	create_mem(&fe_CONCAT19_mem,0,13);
	create_mem(&fe_CONCAT2_mem,0,2);
	create_mem(&fe_CONCAT3_mem,0,4);
	create_mem(&fe_CONCAT4_mem,0,2);
	create_mem(&fe_CONCAT5_mem,0,2);
	create_mem(&fe_CONCAT6_mem,0,4);
	create_mem(&fe_CONCAT7_mem,0,8);
	create_mem(&fe_CONCAT8_mem,0,2);
	create_mem(&fe_CONCAT9_mem,0,3);
	create_mem(&fe_MUX0_mem,0,4);
	create_mem(&fe_MUX1_mem,0,32);
	create_mem(&fe_MUX10_mem,0,32);
	create_mem(&fe_MUX11_mem,0,32);
	create_mem(&fe_MUX12_mem,0,32);
	create_mem(&fe_MUX13_mem,0,32);
	create_mem(&fe_MUX14_mem,0,32);
	create_mem(&fe_MUX15_mem,0,32);
	create_mem(&fe_MUX16_mem,0,32);
	create_mem(&fe_MUX17_mem,0,32);
	create_mem(&fe_MUX18_mem,0,32);
	create_mem(&fe_MUX19_mem,0,32);
	create_mem(&fe_MUX2_mem,0,32);
	create_mem(&fe_MUX20_mem,0,32);
	create_mem(&fe_MUX21_mem,0,32);
	create_mem(&fe_MUX22_mem,0,32);
	create_mem(&fe_MUX23_mem,0,32);
	create_mem(&fe_MUX24_mem,0,32);
	create_mem(&fe_MUX25_mem,0,32);
	create_mem(&fe_MUX26_mem,0,32);
	create_mem(&fe_MUX27_mem,0,32);
	create_mem(&fe_MUX28_mem,0,32);
	create_mem(&fe_MUX29_mem,0,32);
	create_mem(&fe_MUX3_mem,0,32);
	create_mem(&fe_MUX30_mem,0,32);
	create_mem(&fe_MUX31_mem,0,32);
	create_mem(&fe_MUX32_mem,0,32);
	create_mem(&fe_MUX33_mem,0,32);
	create_mem(&fe_MUX34_mem,0,32);
	create_mem(&fe_MUX35_mem,0,32);
	create_mem(&fe_MUX36_mem,0,32);
	create_mem(&fe_MUX37_mem,0,32);
	create_mem(&fe_MUX38_mem,0,32);
	create_mem(&fe_MUX39_mem,0,32);
	create_mem(&fe_MUX4_mem,0,32);
	create_mem(&fe_MUX40_mem,0,32);
	create_mem(&fe_MUX41_mem,0,32);
	create_mem(&fe_MUX42_mem,0,32);
	create_mem(&fe_MUX43_mem,0,32);
	create_mem(&fe_MUX44_mem,0,32);
	create_mem(&fe_MUX45_mem,0,32);
	create_mem(&fe_MUX46_mem,0,32);
	create_mem(&fe_MUX47_mem,0,32);
	create_mem(&fe_MUX48_mem,0,32);
	create_mem(&fe_MUX49_mem,0,32);
	create_mem(&fe_MUX5_mem,0,32);
	create_mem(&fe_MUX50_mem,0,32);
	create_mem(&fe_MUX51_mem,0,13);
	create_mem(&fe_MUX6_mem,0,32);
	create_mem(&fe_MUX7_mem,0,32);
	create_mem(&fe_MUX8_mem,0,32);
	create_mem(&fe_MUX9_mem,0,32);
	create_mem(&fe_NOT0_mem,0,1);
	create_mem(&fe_NOT1_mem,0,1);
	create_mem(&fe_NOT10_mem,0,1);
	create_mem(&fe_NOT11_mem,0,1);
	create_mem(&fe_NOT12_mem,0,1);
	create_mem(&fe_NOT13_mem,0,1);
	create_mem(&fe_NOT14_mem,0,1);
	create_mem(&fe_NOT15_mem,0,1);
	create_mem(&fe_NOT16_mem,0,1);
	create_mem(&fe_NOT17_mem,0,1);
	create_mem(&fe_NOT18_mem,0,1);
	create_mem(&fe_NOT19_mem,0,1);
	create_mem(&fe_NOT2_mem,0,1);
	create_mem(&fe_NOT20_mem,0,1);
	create_mem(&fe_NOT21_mem,0,1);
	create_mem(&fe_NOT22_mem,0,1);
	create_mem(&fe_NOT3_mem,0,1);
	create_mem(&fe_NOT4_mem,0,1);
	create_mem(&fe_NOT5_mem,0,1);
	create_mem(&fe_NOT6_mem,0,1);
	create_mem(&fe_NOT7_mem,0,1);
	create_mem(&fe_NOT8_mem,0,1);
	create_mem(&fe_NOT9_mem,0,1);
	create_mem(&fe_OR0_mem,0,1);
	create_mem(&fe_OR1_mem,0,1);
	create_mem(&fe_OR10_mem,0,1);
	create_mem(&fe_OR11_mem,0,1);
	create_mem(&fe_OR2_mem,0,1);
	create_mem(&fe_OR3_mem,0,1);
	create_mem(&fe_OR4_mem,0,1);
	create_mem(&fe_OR5_mem,0,1);
	create_mem(&fe_OR6_mem,0,1);
	create_mem(&fe_OR7_mem,0,1);
	create_mem(&fe_OR8_mem,0,1);
	create_mem(&fe_OR9_mem,0,1);
	create_mem(&fe_RAM0_mem,0,32);
	create_mem(&fe_REG0_mem,0,32);
	create_mem(&fe_REG1_mem,0,32);
	create_mem(&fe_REG10_mem,0,32);
	create_mem(&fe_REG11_mem,0,32);
	create_mem(&fe_REG12_mem,0,32);
	create_mem(&fe_REG13_mem,0,32);
	create_mem(&fe_REG14_mem,0,32);
	create_mem(&fe_REG15_mem,0,32);
	create_mem(&fe_REG16_mem,0,2);
	create_mem(&fe_REG17_mem,0,13);
	create_mem(&fe_REG2_mem,0,32);
	create_mem(&fe_REG3_mem,0,32);
	create_mem(&fe_REG4_mem,0,32);
	create_mem(&fe_REG5_mem,0,32);
	create_mem(&fe_REG6_mem,0,32);
	create_mem(&fe_REG7_mem,0,32);
	create_mem(&fe_REG8_mem,0,32);
	create_mem(&fe_REG9_mem,0,32);
	create_mem(&fe_ROM0_mem,0,32);
	create_mem(&fe_SELECT0_mem,0,1);
	create_mem(&fe_SELECT1_mem,0,1);
	create_mem(&fe_SELECT10_mem,0,1);
	create_mem(&fe_SELECT11_mem,0,1);
	create_mem(&fe_SELECT12_mem,0,1);
	create_mem(&fe_SELECT13_mem,0,1);
	create_mem(&fe_SELECT14_mem,0,1);
	create_mem(&fe_SELECT15_mem,0,1);
	create_mem(&fe_SELECT16_mem,0,1);
	create_mem(&fe_SELECT17_mem,0,1);
	create_mem(&fe_SELECT18_mem,0,1);
	create_mem(&fe_SELECT19_mem,0,1);
	create_mem(&fe_SELECT2_mem,0,1);
	create_mem(&fe_SELECT20_mem,0,1);
	create_mem(&fe_SELECT21_mem,0,1);
	create_mem(&fe_SELECT22_mem,0,1);
	create_mem(&fe_SELECT23_mem,0,1);
	create_mem(&fe_SELECT24_mem,0,1);
	create_mem(&fe_SELECT25_mem,0,1);
	create_mem(&fe_SELECT26_mem,0,1);
	create_mem(&fe_SELECT27_mem,0,1);
	create_mem(&fe_SELECT28_mem,0,1);
	create_mem(&fe_SELECT29_mem,0,1);
	create_mem(&fe_SELECT3_mem,0,1);
	create_mem(&fe_SELECT30_mem,0,1);
	create_mem(&fe_SELECT31_mem,0,1);
	create_mem(&fe_SELECT32_mem,0,1);
	create_mem(&fe_SELECT33_mem,0,1);
	create_mem(&fe_SELECT34_mem,0,1);
	create_mem(&fe_SELECT35_mem,0,1);
	create_mem(&fe_SELECT36_mem,0,1);
	create_mem(&fe_SELECT37_mem,0,1);
	create_mem(&fe_SELECT38_mem,0,1);
	create_mem(&fe_SELECT39_mem,0,1);
	create_mem(&fe_SELECT4_mem,0,1);
	create_mem(&fe_SELECT40_mem,0,1);
	create_mem(&fe_SELECT41_mem,0,1);
	create_mem(&fe_SELECT42_mem,0,1);
	create_mem(&fe_SELECT43_mem,0,1);
	create_mem(&fe_SELECT44_mem,0,1);
	create_mem(&fe_SELECT5_mem,0,1);
	create_mem(&fe_SELECT6_mem,0,1);
	create_mem(&fe_SELECT7_mem,0,1);
	create_mem(&fe_SELECT8_mem,0,1);
	create_mem(&fe_SELECT9_mem,0,1);
	create_mem(&fe_SLICE0_mem,0,2);
	create_mem(&fe_SLICE1_mem,0,1);
	create_mem(&fe_SLICE10_mem,0,4);
	create_mem(&fe_SLICE11_mem,0,4);
	create_mem(&fe_SLICE12_mem,0,13);
	create_mem(&fe_SLICE13_mem,0,13);
	create_mem(&fe_SLICE14_mem,0,13);
	create_mem(&fe_SLICE15_mem,0,13);
	create_mem(&fe_SLICE2_mem,0,1);
	create_mem(&fe_SLICE3_mem,0,4);
	create_mem(&fe_SLICE4_mem,0,2);
	create_mem(&fe_SLICE5_mem,0,1);
	create_mem(&fe_SLICE6_mem,0,1);
	create_mem(&fe_SLICE7_mem,0,2);
	create_mem(&fe_SLICE8_mem,0,1);
	create_mem(&fe_SLICE9_mem,0,1);
	create_mem(&fe_XOR0_mem,0,1);
	create_mem(&fe_XOR1_mem,0,1);
	create_mem(&fe_XOR10_mem,0,1);
	create_mem(&fe_XOR11_mem,0,1);
	create_mem(&fe_XOR12_mem,0,1);
	create_mem(&fe_XOR2_mem,0,1);
	create_mem(&fe_XOR3_mem,0,1);
	create_mem(&fe_XOR4_mem,0,1);
	create_mem(&fe_XOR5_mem,0,1);
	create_mem(&fe_XOR6_mem,0,1);
	create_mem(&fe_XOR7_mem,0,1);
	create_mem(&fe_XOR8_mem,0,1);
	create_mem(&fe_XOR9_mem,0,1);


    //creation des registres
	create_mem(&fe_MUX51_reg,0,13);
	create_mem(&_my_constant_2__reg,0,2);
	create_mem(&fe_MUX5_reg,0,32);
	create_mem(&fe_MUX6_reg,0,32);
	create_mem(&fe_MUX9_reg,0,32);
	create_mem(&fe_MUX10_reg,0,32);
	create_mem(&fe_MUX15_reg,0,32);
	create_mem(&fe_MUX16_reg,0,32);
	create_mem(&fe_MUX19_reg,0,32);
	create_mem(&fe_MUX20_reg,0,32);
	create_mem(&fe_MUX27_reg,0,32);
	create_mem(&fe_MUX28_reg,0,32);
	create_mem(&fe_MUX31_reg,0,32);
	create_mem(&fe_MUX32_reg,0,32);
	create_mem(&fe_MUX37_reg,0,32);
	create_mem(&fe_MUX38_reg,0,32);
	create_mem(&fe_MUX41_reg,0,32);
	create_mem(&fe_MUX42_reg,0,32);
int fe_RAM0_addr_size=13;
int fe_RAM0_word_size=32;
bool meta=true;
char* clock_registre=fe_MUX42_reg;
char* display=fe_MUX20_reg;
int reg_size=32;
int ram_size_word=fe_RAM0_word_size;
int ram_size_addr=fe_RAM0_addr_size;
char* ram=fe_RAM0_ram;


    //equations
	fe_REG17_fun=([](){
		if(!fe_REG17_bool) copy(fe_MUX51_reg,fe_REG17_mem,0,0,13);
		fe_REG17_bool=true;
		return fe_REG17_mem;
	});
	fe_ROM0_fun=([](){
		if(!fe_ROM0_bool) copy(fe_ROM0_rom,fe_ROM0_mem,to_int(fe_REG17_fun(),0,13),0,32);
		fe_ROM0_bool=true;
		return fe_ROM0_mem;
	});
	fe_SLICE3_fun=([](){
		if(!fe_SLICE3_bool) op_slice(fe_SLICE3_mem,0,3,fe_ROM0_fun());
		fe_SLICE3_bool=true;
		return fe_SLICE3_mem;
	});
	fe_SLICE4_fun=([](){
		if(!fe_SLICE4_bool) op_slice(fe_SLICE4_mem,0,1,fe_SLICE3_fun());
		fe_SLICE4_bool=true;
		return fe_SLICE4_mem;
	});
	fe_SLICE5_fun=([](){
		if(!fe_SLICE5_bool) op_slice(fe_SLICE5_mem,0,0,fe_SLICE4_fun());
		fe_SLICE5_bool=true;
		return fe_SLICE5_mem;
	});
	fe_SLICE6_fun=([](){
		if(!fe_SLICE6_bool) op_slice(fe_SLICE6_mem,1,1,fe_SLICE4_fun());
		fe_SLICE6_bool=true;
		return fe_SLICE6_mem;
	});
	fe_AND7_fun=([](){
		if(!fe_AND7_bool) op_and(fe_AND7_mem,fe_SLICE5_fun(),fe_SLICE6_fun(),1);
		fe_AND7_bool=true;
		return fe_AND7_mem;
	});
	fe_SLICE7_fun=([](){
		if(!fe_SLICE7_bool) op_slice(fe_SLICE7_mem,2,3,fe_SLICE3_fun());
		fe_SLICE7_bool=true;
		return fe_SLICE7_mem;
	});
	fe_SLICE8_fun=([](){
		if(!fe_SLICE8_bool) op_slice(fe_SLICE8_mem,0,0,fe_SLICE7_fun());
		fe_SLICE8_bool=true;
		return fe_SLICE8_mem;
	});
	fe_SLICE9_fun=([](){
		if(!fe_SLICE9_bool) op_slice(fe_SLICE9_mem,1,1,fe_SLICE7_fun());
		fe_SLICE9_bool=true;
		return fe_SLICE9_mem;
	});
	fe_NOT5_fun=([](){
		if(!fe_NOT5_bool) op_not(fe_NOT5_mem,fe_SLICE9_fun(),1);
		fe_NOT5_bool=true;
		return fe_NOT5_mem;
	});
	fe_AND10_fun=([](){
		if(!fe_AND10_bool) op_and(fe_AND10_mem,fe_SLICE8_fun(),fe_NOT5_fun(),1);
		fe_AND10_bool=true;
		return fe_AND10_mem;
	});
	fe_AND26_fun=([](){
		if(!fe_AND26_bool) op_and(fe_AND26_mem,fe_AND7_fun(),fe_AND10_fun(),1);
		fe_AND26_bool=true;
		return fe_AND26_mem;
	});
	fe_REG16_fun=([](){
		if(!fe_REG16_bool) copy(_my_constant_2__reg,fe_REG16_mem,0,0,2);
		fe_REG16_bool=true;
		return fe_REG16_mem;
	});
	fe_SELECT30_fun=([](){
		if(!fe_SELECT30_bool) op_select(fe_SELECT30_mem,1,fe_REG16_fun());
		fe_SELECT30_bool=true;
		return fe_SELECT30_mem;
	});
	fe_NOT22_fun=([](){
		if(!fe_NOT22_bool) op_not(fe_NOT22_mem,fe_SELECT30_fun(),1);
		fe_NOT22_bool=true;
		return fe_NOT22_mem;
	});
	fe_SLICE0_fun=([](){
		if(!fe_SLICE0_bool) op_slice(fe_SLICE0_mem,4,5,fe_ROM0_fun());
		fe_SLICE0_bool=true;
		return fe_SLICE0_mem;
	});
	fe_SLICE1_fun=([](){
		if(!fe_SLICE1_bool) op_slice(fe_SLICE1_mem,0,0,fe_SLICE0_fun());
		fe_SLICE1_bool=true;
		return fe_SLICE1_mem;
	});
	fe_NOT0_fun=([](){
		if(!fe_NOT0_bool) op_not(fe_NOT0_mem,fe_SLICE1_fun(),1);
		fe_NOT0_bool=true;
		return fe_NOT0_mem;
	});
	fe_SLICE2_fun=([](){
		if(!fe_SLICE2_bool) op_slice(fe_SLICE2_mem,1,1,fe_SLICE0_fun());
		fe_SLICE2_bool=true;
		return fe_SLICE2_mem;
	});
	fe_AND1_fun=([](){
		if(!fe_AND1_bool) op_and(fe_AND1_mem,fe_NOT0_fun(),fe_SLICE2_fun(),1);
		fe_AND1_bool=true;
		return fe_AND1_mem;
	});
	fe_AND62_fun=([](){
		if(!fe_AND62_bool) op_and(fe_AND62_mem,fe_NOT22_fun(),fe_AND1_fun(),1);
		fe_AND62_bool=true;
		return fe_AND62_mem;
	});
	fe_NOT1_fun=([](){
		if(!fe_NOT1_bool) op_not(fe_NOT1_mem,fe_SLICE2_fun(),1);
		fe_NOT1_bool=true;
		return fe_NOT1_mem;
	});
	fe_AND2_fun=([](){
		if(!fe_AND2_bool) op_and(fe_AND2_mem,fe_SLICE1_fun(),fe_NOT1_fun(),1);
		fe_AND2_bool=true;
		return fe_AND2_mem;
	});
	fe_AND63_fun=([](){
		if(!fe_AND63_bool) op_and(fe_AND63_mem,fe_SELECT30_fun(),fe_AND2_fun(),1);
		fe_AND63_bool=true;
		return fe_AND63_mem;
	});
	fe_OR9_fun=([](){
		if(!fe_OR9_bool) op_or(fe_OR9_mem,fe_AND62_fun(),fe_AND63_fun(),1);
		fe_OR9_bool=true;
		return fe_OR9_mem;
	});
	fe_SELECT31_fun=([](){
		if(!fe_SELECT31_bool) op_select(fe_SELECT31_mem,1,fe_REG16_fun());
		fe_SELECT31_bool=true;
		return fe_SELECT31_mem;
	});
	fe_AND3_fun=([](){
		if(!fe_AND3_bool) op_and(fe_AND3_mem,fe_SLICE1_fun(),fe_SLICE2_fun(),1);
		fe_AND3_bool=true;
		return fe_AND3_mem;
	});
	fe_AND64_fun=([](){
		if(!fe_AND64_bool) op_and(fe_AND64_mem,fe_SELECT31_fun(),fe_AND3_fun(),1);
		fe_AND64_bool=true;
		return fe_AND64_mem;
	});
	fe_AND0_fun=([](){
		if(!fe_AND0_bool) op_and(fe_AND0_mem,fe_NOT0_fun(),fe_NOT1_fun(),1);
		fe_AND0_bool=true;
		return fe_AND0_mem;
	});
	fe_OR10_fun=([](){
		if(!fe_OR10_bool) op_or(fe_OR10_mem,fe_AND64_fun(),fe_AND0_fun(),1);
		fe_OR10_bool=true;
		return fe_OR10_mem;
	});
	fe_OR11_fun=([](){
		if(!fe_OR11_bool) op_or(fe_OR11_mem,fe_OR9_fun(),fe_OR10_fun(),1);
		fe_OR11_bool=true;
		return fe_OR11_mem;
	});
	fe_AND65_fun=([](){
		if(!fe_AND65_bool) op_and(fe_AND65_mem,fe_AND26_fun(),fe_OR11_fun(),1);
		fe_AND65_bool=true;
		return fe_AND65_mem;
	});
	fe_SELECT43_fun=([](){
		if(!fe_SELECT43_bool) op_select(fe_SELECT43_mem,1,fe_REG17_fun());
		fe_SELECT43_bool=true;
		return fe_SELECT43_mem;
	});
	fe_SELECT42_fun=([](){
		if(!fe_SELECT42_bool) op_select(fe_SELECT42_mem,2,fe_REG17_fun());
		fe_SELECT42_bool=true;
		return fe_SELECT42_mem;
	});
	fe_SELECT41_fun=([](){
		if(!fe_SELECT41_bool) op_select(fe_SELECT41_mem,3,fe_REG17_fun());
		fe_SELECT41_bool=true;
		return fe_SELECT41_mem;
	});
	fe_SELECT40_fun=([](){
		if(!fe_SELECT40_bool) op_select(fe_SELECT40_mem,4,fe_REG17_fun());
		fe_SELECT40_bool=true;
		return fe_SELECT40_mem;
	});
	fe_SELECT39_fun=([](){
		if(!fe_SELECT39_bool) op_select(fe_SELECT39_mem,5,fe_REG17_fun());
		fe_SELECT39_bool=true;
		return fe_SELECT39_mem;
	});
	fe_SELECT38_fun=([](){
		if(!fe_SELECT38_bool) op_select(fe_SELECT38_mem,6,fe_REG17_fun());
		fe_SELECT38_bool=true;
		return fe_SELECT38_mem;
	});
	fe_SELECT37_fun=([](){
		if(!fe_SELECT37_bool) op_select(fe_SELECT37_mem,7,fe_REG17_fun());
		fe_SELECT37_bool=true;
		return fe_SELECT37_mem;
	});
	fe_SELECT36_fun=([](){
		if(!fe_SELECT36_bool) op_select(fe_SELECT36_mem,8,fe_REG17_fun());
		fe_SELECT36_bool=true;
		return fe_SELECT36_mem;
	});
	fe_SELECT35_fun=([](){
		if(!fe_SELECT35_bool) op_select(fe_SELECT35_mem,9,fe_REG17_fun());
		fe_SELECT35_bool=true;
		return fe_SELECT35_mem;
	});
	fe_SELECT34_fun=([](){
		if(!fe_SELECT34_bool) op_select(fe_SELECT34_mem,10,fe_REG17_fun());
		fe_SELECT34_bool=true;
		return fe_SELECT34_mem;
	});
	fe_SELECT33_fun=([](){
		if(!fe_SELECT33_bool) op_select(fe_SELECT33_mem,11,fe_REG17_fun());
		fe_SELECT33_bool=true;
		return fe_SELECT33_mem;
	});
	fe_SELECT32_fun=([](){
		if(!fe_SELECT32_bool) op_select(fe_SELECT32_mem,12,fe_REG17_fun());
		fe_SELECT32_bool=true;
		return fe_SELECT32_mem;
	});
	_my_constant_4__fun=([](){
		if(!_my_constant_4__bool) of_string(_my_constant_4__mem,1,"1");
		_my_constant_4__bool=true;
		return _my_constant_4__mem;
	});
	fe_AND66_fun=([](){
		if(!fe_AND66_bool) op_and(fe_AND66_mem,fe_SELECT32_fun(),_my_constant_4__fun(),1);
		fe_AND66_bool=true;
		return fe_AND66_mem;
	});
	fe_AND67_fun=([](){
		if(!fe_AND67_bool) op_and(fe_AND67_mem,fe_SELECT33_fun(),fe_AND66_fun(),1);
		fe_AND67_bool=true;
		return fe_AND67_mem;
	});
	fe_AND68_fun=([](){
		if(!fe_AND68_bool) op_and(fe_AND68_mem,fe_SELECT34_fun(),fe_AND67_fun(),1);
		fe_AND68_bool=true;
		return fe_AND68_mem;
	});
	fe_AND69_fun=([](){
		if(!fe_AND69_bool) op_and(fe_AND69_mem,fe_SELECT35_fun(),fe_AND68_fun(),1);
		fe_AND69_bool=true;
		return fe_AND69_mem;
	});
	fe_AND70_fun=([](){
		if(!fe_AND70_bool) op_and(fe_AND70_mem,fe_SELECT36_fun(),fe_AND69_fun(),1);
		fe_AND70_bool=true;
		return fe_AND70_mem;
	});
	fe_AND71_fun=([](){
		if(!fe_AND71_bool) op_and(fe_AND71_mem,fe_SELECT37_fun(),fe_AND70_fun(),1);
		fe_AND71_bool=true;
		return fe_AND71_mem;
	});
	fe_AND72_fun=([](){
		if(!fe_AND72_bool) op_and(fe_AND72_mem,fe_SELECT38_fun(),fe_AND71_fun(),1);
		fe_AND72_bool=true;
		return fe_AND72_mem;
	});
	fe_AND73_fun=([](){
		if(!fe_AND73_bool) op_and(fe_AND73_mem,fe_SELECT39_fun(),fe_AND72_fun(),1);
		fe_AND73_bool=true;
		return fe_AND73_mem;
	});
	fe_AND74_fun=([](){
		if(!fe_AND74_bool) op_and(fe_AND74_mem,fe_SELECT40_fun(),fe_AND73_fun(),1);
		fe_AND74_bool=true;
		return fe_AND74_mem;
	});
	fe_AND75_fun=([](){
		if(!fe_AND75_bool) op_and(fe_AND75_mem,fe_SELECT41_fun(),fe_AND74_fun(),1);
		fe_AND75_bool=true;
		return fe_AND75_mem;
	});
	fe_AND76_fun=([](){
		if(!fe_AND76_bool) op_and(fe_AND76_mem,fe_SELECT42_fun(),fe_AND75_fun(),1);
		fe_AND76_bool=true;
		return fe_AND76_mem;
	});
	fe_XOR11_fun=([](){
		if(!fe_XOR11_bool) op_xor(fe_XOR11_mem,fe_SELECT43_fun(),fe_AND76_fun(),1);
		fe_XOR11_bool=true;
		return fe_XOR11_mem;
	});
	fe_XOR10_fun=([](){
		if(!fe_XOR10_bool) op_xor(fe_XOR10_mem,fe_SELECT42_fun(),fe_AND75_fun(),1);
		fe_XOR10_bool=true;
		return fe_XOR10_mem;
	});
	fe_CONCAT8_fun=([](){
		if(!fe_CONCAT8_bool) op_concat(fe_CONCAT8_mem,fe_XOR11_fun(),fe_XOR10_fun(),1,1);
		fe_CONCAT8_bool=true;
		return fe_CONCAT8_mem;
	});
	fe_SELECT44_fun=([](){
		if(!fe_SELECT44_bool) op_select(fe_SELECT44_mem,0,fe_REG17_fun());
		fe_SELECT44_bool=true;
		return fe_SELECT44_mem;
	});
	fe_AND77_fun=([](){
		if(!fe_AND77_bool) op_and(fe_AND77_mem,fe_SELECT43_fun(),fe_AND76_fun(),1);
		fe_AND77_bool=true;
		return fe_AND77_mem;
	});
	fe_XOR12_fun=([](){
		if(!fe_XOR12_bool) op_xor(fe_XOR12_mem,fe_SELECT44_fun(),fe_AND77_fun(),1);
		fe_XOR12_bool=true;
		return fe_XOR12_mem;
	});
	fe_CONCAT9_fun=([](){
		if(!fe_CONCAT9_bool) op_concat(fe_CONCAT9_mem,fe_XOR12_fun(),fe_CONCAT8_fun(),1,2);
		fe_CONCAT9_bool=true;
		return fe_CONCAT9_mem;
	});
	fe_XOR8_fun=([](){
		if(!fe_XOR8_bool) op_xor(fe_XOR8_mem,fe_SELECT40_fun(),fe_AND73_fun(),1);
		fe_XOR8_bool=true;
		return fe_XOR8_mem;
	});
	fe_XOR7_fun=([](){
		if(!fe_XOR7_bool) op_xor(fe_XOR7_mem,fe_SELECT39_fun(),fe_AND72_fun(),1);
		fe_XOR7_bool=true;
		return fe_XOR7_mem;
	});
	fe_CONCAT10_fun=([](){
		if(!fe_CONCAT10_bool) op_concat(fe_CONCAT10_mem,fe_XOR8_fun(),fe_XOR7_fun(),1,1);
		fe_CONCAT10_bool=true;
		return fe_CONCAT10_mem;
	});
	fe_XOR9_fun=([](){
		if(!fe_XOR9_bool) op_xor(fe_XOR9_mem,fe_SELECT41_fun(),fe_AND74_fun(),1);
		fe_XOR9_bool=true;
		return fe_XOR9_mem;
	});
	fe_CONCAT11_fun=([](){
		if(!fe_CONCAT11_bool) op_concat(fe_CONCAT11_mem,fe_XOR9_fun(),fe_CONCAT10_fun(),1,2);
		fe_CONCAT11_bool=true;
		return fe_CONCAT11_mem;
	});
	fe_CONCAT12_fun=([](){
		if(!fe_CONCAT12_bool) op_concat(fe_CONCAT12_mem,fe_CONCAT9_fun(),fe_CONCAT11_fun(),3,3);
		fe_CONCAT12_bool=true;
		return fe_CONCAT12_mem;
	});
	fe_XOR5_fun=([](){
		if(!fe_XOR5_bool) op_xor(fe_XOR5_mem,fe_SELECT37_fun(),fe_AND70_fun(),1);
		fe_XOR5_bool=true;
		return fe_XOR5_mem;
	});
	fe_XOR4_fun=([](){
		if(!fe_XOR4_bool) op_xor(fe_XOR4_mem,fe_SELECT36_fun(),fe_AND69_fun(),1);
		fe_XOR4_bool=true;
		return fe_XOR4_mem;
	});
	fe_CONCAT13_fun=([](){
		if(!fe_CONCAT13_bool) op_concat(fe_CONCAT13_mem,fe_XOR5_fun(),fe_XOR4_fun(),1,1);
		fe_CONCAT13_bool=true;
		return fe_CONCAT13_mem;
	});
	fe_XOR6_fun=([](){
		if(!fe_XOR6_bool) op_xor(fe_XOR6_mem,fe_SELECT38_fun(),fe_AND71_fun(),1);
		fe_XOR6_bool=true;
		return fe_XOR6_mem;
	});
	fe_CONCAT14_fun=([](){
		if(!fe_CONCAT14_bool) op_concat(fe_CONCAT14_mem,fe_XOR6_fun(),fe_CONCAT13_fun(),1,2);
		fe_CONCAT14_bool=true;
		return fe_CONCAT14_mem;
	});
	fe_XOR3_fun=([](){
		if(!fe_XOR3_bool) op_xor(fe_XOR3_mem,fe_SELECT35_fun(),fe_AND68_fun(),1);
		fe_XOR3_bool=true;
		return fe_XOR3_mem;
	});
	fe_XOR2_fun=([](){
		if(!fe_XOR2_bool) op_xor(fe_XOR2_mem,fe_SELECT34_fun(),fe_AND67_fun(),1);
		fe_XOR2_bool=true;
		return fe_XOR2_mem;
	});
	fe_CONCAT15_fun=([](){
		if(!fe_CONCAT15_bool) op_concat(fe_CONCAT15_mem,fe_XOR3_fun(),fe_XOR2_fun(),1,1);
		fe_CONCAT15_bool=true;
		return fe_CONCAT15_mem;
	});
	fe_XOR1_fun=([](){
		if(!fe_XOR1_bool) op_xor(fe_XOR1_mem,fe_SELECT33_fun(),fe_AND66_fun(),1);
		fe_XOR1_bool=true;
		return fe_XOR1_mem;
	});
	_my_constant_3__fun=([](){
		if(!_my_constant_3__bool) of_string(_my_constant_3__mem,1,"1");
		_my_constant_3__bool=true;
		return _my_constant_3__mem;
	});
	fe_XOR0_fun=([](){
		if(!fe_XOR0_bool) op_xor(fe_XOR0_mem,fe_SELECT32_fun(),_my_constant_3__fun(),1);
		fe_XOR0_bool=true;
		return fe_XOR0_mem;
	});
	fe_CONCAT16_fun=([](){
		if(!fe_CONCAT16_bool) op_concat(fe_CONCAT16_mem,fe_XOR1_fun(),fe_XOR0_fun(),1,1);
		fe_CONCAT16_bool=true;
		return fe_CONCAT16_mem;
	});
	fe_CONCAT17_fun=([](){
		if(!fe_CONCAT17_bool) op_concat(fe_CONCAT17_mem,fe_CONCAT15_fun(),fe_CONCAT16_fun(),2,2);
		fe_CONCAT17_bool=true;
		return fe_CONCAT17_mem;
	});
	fe_CONCAT18_fun=([](){
		if(!fe_CONCAT18_bool) op_concat(fe_CONCAT18_mem,fe_CONCAT14_fun(),fe_CONCAT17_fun(),3,4);
		fe_CONCAT18_bool=true;
		return fe_CONCAT18_mem;
	});
	fe_CONCAT19_fun=([](){
		if(!fe_CONCAT19_bool) op_concat(fe_CONCAT19_mem,fe_CONCAT12_fun(),fe_CONCAT18_fun(),6,7);
		fe_CONCAT19_bool=true;
		return fe_CONCAT19_mem;
	});
	fe_AND78_fun=([](){
		if(!fe_AND78_bool) op_and(fe_AND78_mem,fe_SELECT44_fun(),fe_AND77_fun(),1);
		fe_AND78_bool=true;
		return fe_AND78_mem;
	});
	fe_NOT2_fun=([](){
		if(!fe_NOT2_bool) op_not(fe_NOT2_mem,fe_SLICE5_fun(),1);
		fe_NOT2_bool=true;
		return fe_NOT2_mem;
	});
	fe_NOT3_fun=([](){
		if(!fe_NOT3_bool) op_not(fe_NOT3_mem,fe_SLICE6_fun(),1);
		fe_NOT3_bool=true;
		return fe_NOT3_mem;
	});
	fe_AND4_fun=([](){
		if(!fe_AND4_bool) op_and(fe_AND4_mem,fe_NOT2_fun(),fe_NOT3_fun(),1);
		fe_AND4_bool=true;
		return fe_AND4_mem;
	});
	fe_NOT4_fun=([](){
		if(!fe_NOT4_bool) op_not(fe_NOT4_mem,fe_SLICE8_fun(),1);
		fe_NOT4_bool=true;
		return fe_NOT4_mem;
	});
	fe_AND8_fun=([](){
		if(!fe_AND8_bool) op_and(fe_AND8_mem,fe_NOT4_fun(),fe_NOT5_fun(),1);
		fe_AND8_bool=true;
		return fe_AND8_mem;
	});
	fe_AND12_fun=([](){
		if(!fe_AND12_bool) op_and(fe_AND12_mem,fe_AND4_fun(),fe_AND8_fun(),1);
		fe_AND12_bool=true;
		return fe_AND12_mem;
	});
	fe_AND31_fun=([](){
		if(!fe_AND31_bool) op_and(fe_AND31_mem,fe_AND12_fun(),fe_AND3_fun(),1);
		fe_AND31_bool=true;
		return fe_AND31_mem;
	});
	fe_OR8_fun=([](){
		if(!fe_OR8_bool) op_or(fe_OR8_mem,fe_AND31_fun(),fe_AND26_fun(),1);
		fe_OR8_bool=true;
		return fe_OR8_mem;
	});
	fe_AND30_fun=([](){
		if(!fe_AND30_bool) op_and(fe_AND30_mem,fe_AND12_fun(),fe_AND0_fun(),1);
		fe_AND30_bool=true;
		return fe_AND30_mem;
	});
	fe_OR7_fun=([](){
		if(!fe_OR7_bool) op_or(fe_OR7_mem,fe_AND1_fun(),fe_AND2_fun(),1);
		fe_OR7_bool=true;
		return fe_OR7_mem;
	});
	fe_AND29_fun=([](){
		if(!fe_AND29_bool) op_and(fe_AND29_mem,fe_OR7_fun(),fe_AND12_fun(),1);
		fe_AND29_bool=true;
		return fe_AND29_mem;
	});
	fe_AND9_fun=([](){
		if(!fe_AND9_bool) op_and(fe_AND9_mem,fe_NOT4_fun(),fe_SLICE9_fun(),1);
		fe_AND9_bool=true;
		return fe_AND9_mem;
	});
	fe_AND13_fun=([](){
		if(!fe_AND13_bool) op_and(fe_AND13_mem,fe_AND4_fun(),fe_AND9_fun(),1);
		fe_AND13_bool=true;
		return fe_AND13_mem;
	});
	fe_OR4_fun=([](){
		if(!fe_OR4_bool) op_or(fe_OR4_mem,fe_AND13_fun(),fe_AND2_fun(),1);
		fe_OR4_bool=true;
		return fe_OR4_mem;
	});
	_my_constant_0__fun=([](){
		if(!_my_constant_0__bool) of_string(_my_constant_0__mem,19,"0000000000000000000");
		_my_constant_0__bool=true;
		return _my_constant_0__mem;
	});
	fe_SLICE12_fun=([](){
		if(!fe_SLICE12_bool) op_slice(fe_SLICE12_mem,6,18,fe_ROM0_fun());
		fe_SLICE12_bool=true;
		return fe_SLICE12_mem;
	});
	fe_CONCAT0_fun=([](){
		if(!fe_CONCAT0_bool) op_concat(fe_CONCAT0_mem,_my_constant_0__fun(),fe_SLICE12_fun(),19,13);
		fe_CONCAT0_bool=true;
		return fe_CONCAT0_mem;
	});
	fe_SLICE10_fun=([](){
		if(!fe_SLICE10_bool) op_slice(fe_SLICE10_mem,15,18,fe_ROM0_fun());
		fe_SLICE10_bool=true;
		return fe_SLICE10_mem;
	});
	fe_SELECT0_fun=([](){
		if(!fe_SELECT0_bool) op_select(fe_SELECT0_mem,3,fe_SLICE10_fun());
		fe_SELECT0_bool=true;
		return fe_SELECT0_mem;
	});
	fe_SELECT2_fun=([](){
		if(!fe_SELECT2_bool) op_select(fe_SELECT2_mem,2,fe_SLICE10_fun());
		fe_SELECT2_bool=true;
		return fe_SELECT2_mem;
	});
	fe_SELECT4_fun=([](){
		if(!fe_SELECT4_bool) op_select(fe_SELECT4_mem,1,fe_SLICE10_fun());
		fe_SELECT4_bool=true;
		return fe_SELECT4_mem;
	});
	fe_SELECT6_fun=([](){
		if(!fe_SELECT6_bool) op_select(fe_SELECT6_mem,0,fe_SLICE10_fun());
		fe_SELECT6_bool=true;
		return fe_SELECT6_mem;
	});
	fe_REG0_fun=([](){
		if(!fe_REG0_bool) copy(fe_MUX5_reg,fe_REG0_mem,0,0,32);
		fe_REG0_bool=true;
		return fe_REG0_mem;
	});
	fe_REG1_fun=([](){
		if(!fe_REG1_bool) copy(fe_MUX6_reg,fe_REG1_mem,0,0,32);
		fe_REG1_bool=true;
		return fe_REG1_mem;
	});
	fe_MUX7_fun=([](){
		if(!fe_MUX7_bool) op_mux(fe_MUX7_mem,fe_SELECT6_fun(),fe_REG0_fun(),fe_REG1_fun(),32);
		fe_MUX7_bool=true;
		return fe_MUX7_mem;
	});
	fe_SELECT8_fun=([](){
		if(!fe_SELECT8_bool) op_select(fe_SELECT8_mem,0,fe_SLICE10_fun());
		fe_SELECT8_bool=true;
		return fe_SELECT8_mem;
	});
	fe_REG2_fun=([](){
		if(!fe_REG2_bool) copy(fe_MUX9_reg,fe_REG2_mem,0,0,32);
		fe_REG2_bool=true;
		return fe_REG2_mem;
	});
	fe_REG3_fun=([](){
		if(!fe_REG3_bool) copy(fe_MUX10_reg,fe_REG3_mem,0,0,32);
		fe_REG3_bool=true;
		return fe_REG3_mem;
	});
	fe_MUX11_fun=([](){
		if(!fe_MUX11_bool) op_mux(fe_MUX11_mem,fe_SELECT8_fun(),fe_REG2_fun(),fe_REG3_fun(),32);
		fe_MUX11_bool=true;
		return fe_MUX11_mem;
	});
	fe_MUX13_fun=([](){
		if(!fe_MUX13_bool) op_mux(fe_MUX13_mem,fe_SELECT4_fun(),fe_MUX7_fun(),fe_MUX11_fun(),32);
		fe_MUX13_bool=true;
		return fe_MUX13_mem;
	});
	fe_SELECT10_fun=([](){
		if(!fe_SELECT10_bool) op_select(fe_SELECT10_mem,1,fe_SLICE10_fun());
		fe_SELECT10_bool=true;
		return fe_SELECT10_mem;
	});
	fe_SELECT12_fun=([](){
		if(!fe_SELECT12_bool) op_select(fe_SELECT12_mem,0,fe_SLICE10_fun());
		fe_SELECT12_bool=true;
		return fe_SELECT12_mem;
	});
	fe_REG4_fun=([](){
		if(!fe_REG4_bool) copy(fe_MUX15_reg,fe_REG4_mem,0,0,32);
		fe_REG4_bool=true;
		return fe_REG4_mem;
	});
	fe_REG5_fun=([](){
		if(!fe_REG5_bool) copy(fe_MUX16_reg,fe_REG5_mem,0,0,32);
		fe_REG5_bool=true;
		return fe_REG5_mem;
	});
	fe_MUX17_fun=([](){
		if(!fe_MUX17_bool) op_mux(fe_MUX17_mem,fe_SELECT12_fun(),fe_REG4_fun(),fe_REG5_fun(),32);
		fe_MUX17_bool=true;
		return fe_MUX17_mem;
	});
	fe_SELECT14_fun=([](){
		if(!fe_SELECT14_bool) op_select(fe_SELECT14_mem,0,fe_SLICE10_fun());
		fe_SELECT14_bool=true;
		return fe_SELECT14_mem;
	});
	fe_REG6_fun=([](){
		if(!fe_REG6_bool) copy(fe_MUX19_reg,fe_REG6_mem,0,0,32);
		fe_REG6_bool=true;
		return fe_REG6_mem;
	});
	fe_REG7_fun=([](){
		if(!fe_REG7_bool) copy(fe_MUX20_reg,fe_REG7_mem,0,0,32);
		fe_REG7_bool=true;
		return fe_REG7_mem;
	});
	fe_MUX21_fun=([](){
		if(!fe_MUX21_bool) op_mux(fe_MUX21_mem,fe_SELECT14_fun(),fe_REG6_fun(),fe_REG7_fun(),32);
		fe_MUX21_bool=true;
		return fe_MUX21_mem;
	});
	fe_MUX23_fun=([](){
		if(!fe_MUX23_bool) op_mux(fe_MUX23_mem,fe_SELECT10_fun(),fe_MUX17_fun(),fe_MUX21_fun(),32);
		fe_MUX23_bool=true;
		return fe_MUX23_mem;
	});
	fe_MUX25_fun=([](){
		if(!fe_MUX25_bool) op_mux(fe_MUX25_mem,fe_SELECT2_fun(),fe_MUX13_fun(),fe_MUX23_fun(),32);
		fe_MUX25_bool=true;
		return fe_MUX25_mem;
	});
	fe_SELECT16_fun=([](){
		if(!fe_SELECT16_bool) op_select(fe_SELECT16_mem,2,fe_SLICE10_fun());
		fe_SELECT16_bool=true;
		return fe_SELECT16_mem;
	});
	fe_SELECT18_fun=([](){
		if(!fe_SELECT18_bool) op_select(fe_SELECT18_mem,1,fe_SLICE10_fun());
		fe_SELECT18_bool=true;
		return fe_SELECT18_mem;
	});
	fe_SELECT20_fun=([](){
		if(!fe_SELECT20_bool) op_select(fe_SELECT20_mem,0,fe_SLICE10_fun());
		fe_SELECT20_bool=true;
		return fe_SELECT20_mem;
	});
	fe_REG8_fun=([](){
		if(!fe_REG8_bool) copy(fe_MUX27_reg,fe_REG8_mem,0,0,32);
		fe_REG8_bool=true;
		return fe_REG8_mem;
	});
	fe_REG9_fun=([](){
		if(!fe_REG9_bool) copy(fe_MUX28_reg,fe_REG9_mem,0,0,32);
		fe_REG9_bool=true;
		return fe_REG9_mem;
	});
	fe_MUX29_fun=([](){
		if(!fe_MUX29_bool) op_mux(fe_MUX29_mem,fe_SELECT20_fun(),fe_REG8_fun(),fe_REG9_fun(),32);
		fe_MUX29_bool=true;
		return fe_MUX29_mem;
	});
	fe_SELECT22_fun=([](){
		if(!fe_SELECT22_bool) op_select(fe_SELECT22_mem,0,fe_SLICE10_fun());
		fe_SELECT22_bool=true;
		return fe_SELECT22_mem;
	});
	fe_REG10_fun=([](){
		if(!fe_REG10_bool) copy(fe_MUX31_reg,fe_REG10_mem,0,0,32);
		fe_REG10_bool=true;
		return fe_REG10_mem;
	});
	fe_REG11_fun=([](){
		if(!fe_REG11_bool) copy(fe_MUX32_reg,fe_REG11_mem,0,0,32);
		fe_REG11_bool=true;
		return fe_REG11_mem;
	});
	fe_MUX33_fun=([](){
		if(!fe_MUX33_bool) op_mux(fe_MUX33_mem,fe_SELECT22_fun(),fe_REG10_fun(),fe_REG11_fun(),32);
		fe_MUX33_bool=true;
		return fe_MUX33_mem;
	});
	fe_MUX35_fun=([](){
		if(!fe_MUX35_bool) op_mux(fe_MUX35_mem,fe_SELECT18_fun(),fe_MUX29_fun(),fe_MUX33_fun(),32);
		fe_MUX35_bool=true;
		return fe_MUX35_mem;
	});
	fe_SELECT24_fun=([](){
		if(!fe_SELECT24_bool) op_select(fe_SELECT24_mem,1,fe_SLICE10_fun());
		fe_SELECT24_bool=true;
		return fe_SELECT24_mem;
	});
	fe_SELECT26_fun=([](){
		if(!fe_SELECT26_bool) op_select(fe_SELECT26_mem,0,fe_SLICE10_fun());
		fe_SELECT26_bool=true;
		return fe_SELECT26_mem;
	});
	fe_REG12_fun=([](){
		if(!fe_REG12_bool) copy(fe_MUX37_reg,fe_REG12_mem,0,0,32);
		fe_REG12_bool=true;
		return fe_REG12_mem;
	});
	fe_REG13_fun=([](){
		if(!fe_REG13_bool) copy(fe_MUX38_reg,fe_REG13_mem,0,0,32);
		fe_REG13_bool=true;
		return fe_REG13_mem;
	});
	fe_MUX39_fun=([](){
		if(!fe_MUX39_bool) op_mux(fe_MUX39_mem,fe_SELECT26_fun(),fe_REG12_fun(),fe_REG13_fun(),32);
		fe_MUX39_bool=true;
		return fe_MUX39_mem;
	});
	fe_SELECT28_fun=([](){
		if(!fe_SELECT28_bool) op_select(fe_SELECT28_mem,0,fe_SLICE10_fun());
		fe_SELECT28_bool=true;
		return fe_SELECT28_mem;
	});
	fe_REG14_fun=([](){
		if(!fe_REG14_bool) copy(fe_MUX41_reg,fe_REG14_mem,0,0,32);
		fe_REG14_bool=true;
		return fe_REG14_mem;
	});
	fe_REG15_fun=([](){
		if(!fe_REG15_bool) copy(fe_MUX42_reg,fe_REG15_mem,0,0,32);
		fe_REG15_bool=true;
		return fe_REG15_mem;
	});
	fe_MUX43_fun=([](){
		if(!fe_MUX43_bool) op_mux(fe_MUX43_mem,fe_SELECT28_fun(),fe_REG14_fun(),fe_REG15_fun(),32);
		fe_MUX43_bool=true;
		return fe_MUX43_mem;
	});
	fe_MUX45_fun=([](){
		if(!fe_MUX45_bool) op_mux(fe_MUX45_mem,fe_SELECT24_fun(),fe_MUX39_fun(),fe_MUX43_fun(),32);
		fe_MUX45_bool=true;
		return fe_MUX45_mem;
	});
	fe_MUX47_fun=([](){
		if(!fe_MUX47_bool) op_mux(fe_MUX47_mem,fe_SELECT16_fun(),fe_MUX35_fun(),fe_MUX45_fun(),32);
		fe_MUX47_bool=true;
		return fe_MUX47_mem;
	});
	fe_MUX49_fun=([](){
		if(!fe_MUX49_bool) op_mux(fe_MUX49_mem,fe_SELECT0_fun(),fe_MUX25_fun(),fe_MUX47_fun(),32);
		fe_MUX49_bool=true;
		return fe_MUX49_mem;
	});
	fe_MUX1_fun=([](){
		if(!fe_MUX1_bool) op_mux(fe_MUX1_mem,fe_OR4_fun(),fe_CONCAT0_fun(),fe_MUX49_fun(),32);
		fe_MUX1_bool=true;
		return fe_MUX1_mem;
	});
	fe_MUX2_fun=([](){
		if(!fe_MUX2_bool) op_mux(fe_MUX2_mem,fe_AND29_fun(),fe_MUX1_fun(),fe_MUX49_fun(),32);
		fe_MUX2_bool=true;
		return fe_MUX2_mem;
	});
	fe_SLICE13_fun=([](){
		if(!fe_SLICE13_bool) op_slice(fe_SLICE13_mem,19,31,fe_MUX49_fun());
		fe_SLICE13_bool=true;
		return fe_SLICE13_mem;
	});
	fe_RAM0_fun=([](){
		if(!fe_RAM0_bool) copy(fe_RAM0_ram,fe_RAM0_mem,to_int(fe_SLICE13_fun(),0,13),0,32);
		fe_RAM0_bool=true;
		return fe_RAM0_mem;
	});
	fe_MUX3_fun=([](){
		if(!fe_MUX3_bool) op_mux(fe_MUX3_mem,fe_AND30_fun(),fe_MUX2_fun(),fe_RAM0_fun(),32);
		fe_MUX3_bool=true;
		return fe_MUX3_mem;
	});
	fe_MUX4_fun=([](){
		if(!fe_MUX4_bool) op_mux(fe_MUX4_mem,fe_OR8_fun(),fe_MUX3_fun(),fe_CONCAT0_fun(),32);
		fe_MUX4_bool=true;
		return fe_MUX4_mem;
	});
	fe_SLICE15_fun=([](){
		if(!fe_SLICE15_bool) op_slice(fe_SLICE15_mem,19,31,fe_MUX4_fun());
		fe_SLICE15_bool=true;
		return fe_SLICE15_mem;
	});
	fe_MUX51_fun=([](){
		if(!fe_MUX51_bool) op_mux(fe_MUX51_mem,fe_AND65_fun(),fe_CONCAT19_fun(),fe_SLICE15_fun(),13);
		fe_MUX51_bool=true;
		return fe_MUX51_mem;
	});
	fe_SLICE11_fun=([](){
		if(!fe_SLICE11_bool) op_slice(fe_SLICE11_mem,28,31,fe_ROM0_fun());
		fe_SLICE11_bool=true;
		return fe_SLICE11_mem;
	});
	fe_MUX0_fun=([](){
		if(!fe_MUX0_bool) op_mux(fe_MUX0_mem,fe_AND13_fun(),fe_SLICE11_fun(),fe_SLICE10_fun(),4);
		fe_MUX0_bool=true;
		return fe_MUX0_mem;
	});
	fe_SELECT1_fun=([](){
		if(!fe_SELECT1_bool) op_select(fe_SELECT1_mem,3,fe_MUX0_fun());
		fe_SELECT1_bool=true;
		return fe_SELECT1_mem;
	});
	fe_SELECT3_fun=([](){
		if(!fe_SELECT3_bool) op_select(fe_SELECT3_mem,2,fe_MUX0_fun());
		fe_SELECT3_bool=true;
		return fe_SELECT3_mem;
	});
	fe_SELECT5_fun=([](){
		if(!fe_SELECT5_bool) op_select(fe_SELECT5_mem,1,fe_MUX0_fun());
		fe_SELECT5_bool=true;
		return fe_SELECT5_mem;
	});
	fe_SELECT7_fun=([](){
		if(!fe_SELECT7_bool) op_select(fe_SELECT7_mem,0,fe_MUX0_fun());
		fe_SELECT7_bool=true;
		return fe_SELECT7_mem;
	});
	fe_MUX8_fun=([](){
		if(!fe_MUX8_bool) op_mux(fe_MUX8_mem,fe_SELECT7_fun(),fe_REG0_fun(),fe_REG1_fun(),32);
		fe_MUX8_bool=true;
		return fe_MUX8_mem;
	});
	fe_SELECT9_fun=([](){
		if(!fe_SELECT9_bool) op_select(fe_SELECT9_mem,0,fe_MUX0_fun());
		fe_SELECT9_bool=true;
		return fe_SELECT9_mem;
	});
	fe_MUX12_fun=([](){
		if(!fe_MUX12_bool) op_mux(fe_MUX12_mem,fe_SELECT9_fun(),fe_REG2_fun(),fe_REG3_fun(),32);
		fe_MUX12_bool=true;
		return fe_MUX12_mem;
	});
	fe_MUX14_fun=([](){
		if(!fe_MUX14_bool) op_mux(fe_MUX14_mem,fe_SELECT5_fun(),fe_MUX8_fun(),fe_MUX12_fun(),32);
		fe_MUX14_bool=true;
		return fe_MUX14_mem;
	});
	fe_SELECT11_fun=([](){
		if(!fe_SELECT11_bool) op_select(fe_SELECT11_mem,1,fe_MUX0_fun());
		fe_SELECT11_bool=true;
		return fe_SELECT11_mem;
	});
	fe_SELECT13_fun=([](){
		if(!fe_SELECT13_bool) op_select(fe_SELECT13_mem,0,fe_MUX0_fun());
		fe_SELECT13_bool=true;
		return fe_SELECT13_mem;
	});
	fe_MUX18_fun=([](){
		if(!fe_MUX18_bool) op_mux(fe_MUX18_mem,fe_SELECT13_fun(),fe_REG4_fun(),fe_REG5_fun(),32);
		fe_MUX18_bool=true;
		return fe_MUX18_mem;
	});
	fe_SELECT15_fun=([](){
		if(!fe_SELECT15_bool) op_select(fe_SELECT15_mem,0,fe_MUX0_fun());
		fe_SELECT15_bool=true;
		return fe_SELECT15_mem;
	});
	fe_MUX22_fun=([](){
		if(!fe_MUX22_bool) op_mux(fe_MUX22_mem,fe_SELECT15_fun(),fe_REG6_fun(),fe_REG7_fun(),32);
		fe_MUX22_bool=true;
		return fe_MUX22_mem;
	});
	fe_MUX24_fun=([](){
		if(!fe_MUX24_bool) op_mux(fe_MUX24_mem,fe_SELECT11_fun(),fe_MUX18_fun(),fe_MUX22_fun(),32);
		fe_MUX24_bool=true;
		return fe_MUX24_mem;
	});
	fe_MUX26_fun=([](){
		if(!fe_MUX26_bool) op_mux(fe_MUX26_mem,fe_SELECT3_fun(),fe_MUX14_fun(),fe_MUX24_fun(),32);
		fe_MUX26_bool=true;
		return fe_MUX26_mem;
	});
	fe_SELECT17_fun=([](){
		if(!fe_SELECT17_bool) op_select(fe_SELECT17_mem,2,fe_MUX0_fun());
		fe_SELECT17_bool=true;
		return fe_SELECT17_mem;
	});
	fe_SELECT19_fun=([](){
		if(!fe_SELECT19_bool) op_select(fe_SELECT19_mem,1,fe_MUX0_fun());
		fe_SELECT19_bool=true;
		return fe_SELECT19_mem;
	});
	fe_SELECT21_fun=([](){
		if(!fe_SELECT21_bool) op_select(fe_SELECT21_mem,0,fe_MUX0_fun());
		fe_SELECT21_bool=true;
		return fe_SELECT21_mem;
	});
	fe_MUX30_fun=([](){
		if(!fe_MUX30_bool) op_mux(fe_MUX30_mem,fe_SELECT21_fun(),fe_REG8_fun(),fe_REG9_fun(),32);
		fe_MUX30_bool=true;
		return fe_MUX30_mem;
	});
	fe_SELECT23_fun=([](){
		if(!fe_SELECT23_bool) op_select(fe_SELECT23_mem,0,fe_MUX0_fun());
		fe_SELECT23_bool=true;
		return fe_SELECT23_mem;
	});
	fe_MUX34_fun=([](){
		if(!fe_MUX34_bool) op_mux(fe_MUX34_mem,fe_SELECT23_fun(),fe_REG10_fun(),fe_REG11_fun(),32);
		fe_MUX34_bool=true;
		return fe_MUX34_mem;
	});
	fe_MUX36_fun=([](){
		if(!fe_MUX36_bool) op_mux(fe_MUX36_mem,fe_SELECT19_fun(),fe_MUX30_fun(),fe_MUX34_fun(),32);
		fe_MUX36_bool=true;
		return fe_MUX36_mem;
	});
	fe_SELECT25_fun=([](){
		if(!fe_SELECT25_bool) op_select(fe_SELECT25_mem,1,fe_MUX0_fun());
		fe_SELECT25_bool=true;
		return fe_SELECT25_mem;
	});
	fe_SELECT27_fun=([](){
		if(!fe_SELECT27_bool) op_select(fe_SELECT27_mem,0,fe_MUX0_fun());
		fe_SELECT27_bool=true;
		return fe_SELECT27_mem;
	});
	fe_MUX40_fun=([](){
		if(!fe_MUX40_bool) op_mux(fe_MUX40_mem,fe_SELECT27_fun(),fe_REG12_fun(),fe_REG13_fun(),32);
		fe_MUX40_bool=true;
		return fe_MUX40_mem;
	});
	fe_SELECT29_fun=([](){
		if(!fe_SELECT29_bool) op_select(fe_SELECT29_mem,0,fe_MUX0_fun());
		fe_SELECT29_bool=true;
		return fe_SELECT29_mem;
	});
	fe_MUX44_fun=([](){
		if(!fe_MUX44_bool) op_mux(fe_MUX44_mem,fe_SELECT29_fun(),fe_REG14_fun(),fe_REG15_fun(),32);
		fe_MUX44_bool=true;
		return fe_MUX44_mem;
	});
	fe_MUX46_fun=([](){
		if(!fe_MUX46_bool) op_mux(fe_MUX46_mem,fe_SELECT25_fun(),fe_MUX40_fun(),fe_MUX44_fun(),32);
		fe_MUX46_bool=true;
		return fe_MUX46_mem;
	});
	fe_MUX48_fun=([](){
		if(!fe_MUX48_bool) op_mux(fe_MUX48_mem,fe_SELECT17_fun(),fe_MUX36_fun(),fe_MUX46_fun(),32);
		fe_MUX48_bool=true;
		return fe_MUX48_mem;
	});
	fe_MUX50_fun=([](){
		if(!fe_MUX50_bool) op_mux(fe_MUX50_mem,fe_SELECT1_fun(),fe_MUX26_fun(),fe_MUX48_fun(),32);
		fe_MUX50_bool=true;
		return fe_MUX50_mem;
	});
	fe_SLICE14_fun=([](){
		if(!fe_SLICE14_bool) op_slice(fe_SLICE14_mem,19,31,fe_MUX50_fun());
		fe_SLICE14_bool=true;
		return fe_SLICE14_mem;
	});
	fe_OR0_fun=([](){
		if(!fe_OR0_bool) op_or(fe_OR0_mem,fe_AND1_fun(),fe_AND26_fun(),1);
		fe_OR0_bool=true;
		return fe_OR0_mem;
	});
	fe_AND25_fun=([](){
		if(!fe_AND25_bool) op_and(fe_AND25_mem,fe_AND7_fun(),fe_AND9_fun(),1);
		fe_AND25_bool=true;
		return fe_AND25_mem;
	});
	fe_AND24_fun=([](){
		if(!fe_AND24_bool) op_and(fe_AND24_mem,fe_AND7_fun(),fe_AND8_fun(),1);
		fe_AND24_bool=true;
		return fe_AND24_mem;
	});
	fe_OR1_fun=([](){
		if(!fe_OR1_bool) op_or(fe_OR1_mem,fe_AND25_fun(),fe_AND24_fun(),1);
		fe_OR1_bool=true;
		return fe_OR1_mem;
	});
	fe_OR2_fun=([](){
		if(!fe_OR2_bool) op_or(fe_OR2_mem,fe_OR0_fun(),fe_OR1_fun(),1);
		fe_OR2_bool=true;
		return fe_OR2_mem;
	});
	fe_NOT6_fun=([](){
		if(!fe_NOT6_bool) op_not(fe_NOT6_mem,fe_OR2_fun(),1);
		fe_NOT6_bool=true;
		return fe_NOT6_mem;
	});
	fe_OR3_fun=([](){
		if(!fe_OR3_bool) op_or(fe_OR3_mem,fe_AND13_fun(),fe_NOT6_fun(),1);
		fe_OR3_bool=true;
		return fe_OR3_mem;
	});
	fe_AND33_fun=([](){
		if(!fe_AND33_bool) op_and(fe_AND33_mem,fe_OR3_fun(),fe_SELECT1_fun(),1);
		fe_AND33_bool=true;
		return fe_AND33_mem;
	});
	fe_AND49_fun=([](){
		if(!fe_AND49_bool) op_and(fe_AND49_mem,fe_AND33_fun(),fe_SELECT17_fun(),1);
		fe_AND49_bool=true;
		return fe_AND49_mem;
	});
	fe_AND57_fun=([](){
		if(!fe_AND57_bool) op_and(fe_AND57_mem,fe_AND49_fun(),fe_SELECT25_fun(),1);
		fe_AND57_bool=true;
		return fe_AND57_mem;
	});
	fe_AND61_fun=([](){
		if(!fe_AND61_bool) op_and(fe_AND61_mem,fe_AND57_fun(),fe_SELECT29_fun(),1);
		fe_AND61_bool=true;
		return fe_AND61_mem;
	});
	fe_MUX42_fun=([](){
		if(!fe_MUX42_bool) op_mux(fe_MUX42_mem,fe_AND61_fun(),fe_REG15_fun(),fe_MUX4_fun(),32);
		fe_MUX42_bool=true;
		return fe_MUX42_mem;
	});
	fe_NOT21_fun=([](){
		if(!fe_NOT21_bool) op_not(fe_NOT21_mem,fe_SELECT29_fun(),1);
		fe_NOT21_bool=true;
		return fe_NOT21_mem;
	});
	fe_AND60_fun=([](){
		if(!fe_AND60_bool) op_and(fe_AND60_mem,fe_AND57_fun(),fe_NOT21_fun(),1);
		fe_AND60_bool=true;
		return fe_AND60_mem;
	});
	fe_MUX41_fun=([](){
		if(!fe_MUX41_bool) op_mux(fe_MUX41_mem,fe_AND60_fun(),fe_REG14_fun(),fe_MUX4_fun(),32);
		fe_MUX41_bool=true;
		return fe_MUX41_mem;
	});
	fe_NOT19_fun=([](){
		if(!fe_NOT19_bool) op_not(fe_NOT19_mem,fe_SELECT25_fun(),1);
		fe_NOT19_bool=true;
		return fe_NOT19_mem;
	});
	fe_AND56_fun=([](){
		if(!fe_AND56_bool) op_and(fe_AND56_mem,fe_AND49_fun(),fe_NOT19_fun(),1);
		fe_AND56_bool=true;
		return fe_AND56_mem;
	});
	fe_AND59_fun=([](){
		if(!fe_AND59_bool) op_and(fe_AND59_mem,fe_AND56_fun(),fe_SELECT27_fun(),1);
		fe_AND59_bool=true;
		return fe_AND59_mem;
	});
	fe_MUX38_fun=([](){
		if(!fe_MUX38_bool) op_mux(fe_MUX38_mem,fe_AND59_fun(),fe_REG13_fun(),fe_MUX4_fun(),32);
		fe_MUX38_bool=true;
		return fe_MUX38_mem;
	});
	fe_NOT20_fun=([](){
		if(!fe_NOT20_bool) op_not(fe_NOT20_mem,fe_SELECT27_fun(),1);
		fe_NOT20_bool=true;
		return fe_NOT20_mem;
	});
	fe_AND58_fun=([](){
		if(!fe_AND58_bool) op_and(fe_AND58_mem,fe_AND56_fun(),fe_NOT20_fun(),1);
		fe_AND58_bool=true;
		return fe_AND58_mem;
	});
	fe_MUX37_fun=([](){
		if(!fe_MUX37_bool) op_mux(fe_MUX37_mem,fe_AND58_fun(),fe_REG12_fun(),fe_MUX4_fun(),32);
		fe_MUX37_bool=true;
		return fe_MUX37_mem;
	});
	fe_NOT15_fun=([](){
		if(!fe_NOT15_bool) op_not(fe_NOT15_mem,fe_SELECT17_fun(),1);
		fe_NOT15_bool=true;
		return fe_NOT15_mem;
	});
	fe_AND48_fun=([](){
		if(!fe_AND48_bool) op_and(fe_AND48_mem,fe_AND33_fun(),fe_NOT15_fun(),1);
		fe_AND48_bool=true;
		return fe_AND48_mem;
	});
	fe_AND51_fun=([](){
		if(!fe_AND51_bool) op_and(fe_AND51_mem,fe_AND48_fun(),fe_SELECT19_fun(),1);
		fe_AND51_bool=true;
		return fe_AND51_mem;
	});
	fe_AND55_fun=([](){
		if(!fe_AND55_bool) op_and(fe_AND55_mem,fe_AND51_fun(),fe_SELECT23_fun(),1);
		fe_AND55_bool=true;
		return fe_AND55_mem;
	});
	fe_MUX32_fun=([](){
		if(!fe_MUX32_bool) op_mux(fe_MUX32_mem,fe_AND55_fun(),fe_REG11_fun(),fe_MUX4_fun(),32);
		fe_MUX32_bool=true;
		return fe_MUX32_mem;
	});
	fe_NOT18_fun=([](){
		if(!fe_NOT18_bool) op_not(fe_NOT18_mem,fe_SELECT23_fun(),1);
		fe_NOT18_bool=true;
		return fe_NOT18_mem;
	});
	fe_AND54_fun=([](){
		if(!fe_AND54_bool) op_and(fe_AND54_mem,fe_AND51_fun(),fe_NOT18_fun(),1);
		fe_AND54_bool=true;
		return fe_AND54_mem;
	});
	fe_MUX31_fun=([](){
		if(!fe_MUX31_bool) op_mux(fe_MUX31_mem,fe_AND54_fun(),fe_REG10_fun(),fe_MUX4_fun(),32);
		fe_MUX31_bool=true;
		return fe_MUX31_mem;
	});
	fe_NOT16_fun=([](){
		if(!fe_NOT16_bool) op_not(fe_NOT16_mem,fe_SELECT19_fun(),1);
		fe_NOT16_bool=true;
		return fe_NOT16_mem;
	});
	fe_AND50_fun=([](){
		if(!fe_AND50_bool) op_and(fe_AND50_mem,fe_AND48_fun(),fe_NOT16_fun(),1);
		fe_AND50_bool=true;
		return fe_AND50_mem;
	});
	fe_AND53_fun=([](){
		if(!fe_AND53_bool) op_and(fe_AND53_mem,fe_AND50_fun(),fe_SELECT21_fun(),1);
		fe_AND53_bool=true;
		return fe_AND53_mem;
	});
	fe_MUX28_fun=([](){
		if(!fe_MUX28_bool) op_mux(fe_MUX28_mem,fe_AND53_fun(),fe_REG9_fun(),fe_MUX4_fun(),32);
		fe_MUX28_bool=true;
		return fe_MUX28_mem;
	});
	fe_NOT17_fun=([](){
		if(!fe_NOT17_bool) op_not(fe_NOT17_mem,fe_SELECT21_fun(),1);
		fe_NOT17_bool=true;
		return fe_NOT17_mem;
	});
	fe_AND52_fun=([](){
		if(!fe_AND52_bool) op_and(fe_AND52_mem,fe_AND50_fun(),fe_NOT17_fun(),1);
		fe_AND52_bool=true;
		return fe_AND52_mem;
	});
	fe_MUX27_fun=([](){
		if(!fe_MUX27_bool) op_mux(fe_MUX27_mem,fe_AND52_fun(),fe_REG8_fun(),fe_MUX4_fun(),32);
		fe_MUX27_bool=true;
		return fe_MUX27_mem;
	});
	fe_NOT7_fun=([](){
		if(!fe_NOT7_bool) op_not(fe_NOT7_mem,fe_SELECT1_fun(),1);
		fe_NOT7_bool=true;
		return fe_NOT7_mem;
	});
	fe_AND32_fun=([](){
		if(!fe_AND32_bool) op_and(fe_AND32_mem,fe_OR3_fun(),fe_NOT7_fun(),1);
		fe_AND32_bool=true;
		return fe_AND32_mem;
	});
	fe_AND35_fun=([](){
		if(!fe_AND35_bool) op_and(fe_AND35_mem,fe_AND32_fun(),fe_SELECT3_fun(),1);
		fe_AND35_bool=true;
		return fe_AND35_mem;
	});
	fe_AND43_fun=([](){
		if(!fe_AND43_bool) op_and(fe_AND43_mem,fe_AND35_fun(),fe_SELECT11_fun(),1);
		fe_AND43_bool=true;
		return fe_AND43_mem;
	});
	fe_AND47_fun=([](){
		if(!fe_AND47_bool) op_and(fe_AND47_mem,fe_AND43_fun(),fe_SELECT15_fun(),1);
		fe_AND47_bool=true;
		return fe_AND47_mem;
	});
	fe_MUX20_fun=([](){
		if(!fe_MUX20_bool) op_mux(fe_MUX20_mem,fe_AND47_fun(),fe_REG7_fun(),fe_MUX4_fun(),32);
		fe_MUX20_bool=true;
		return fe_MUX20_mem;
	});
	fe_NOT14_fun=([](){
		if(!fe_NOT14_bool) op_not(fe_NOT14_mem,fe_SELECT15_fun(),1);
		fe_NOT14_bool=true;
		return fe_NOT14_mem;
	});
	fe_AND46_fun=([](){
		if(!fe_AND46_bool) op_and(fe_AND46_mem,fe_AND43_fun(),fe_NOT14_fun(),1);
		fe_AND46_bool=true;
		return fe_AND46_mem;
	});
	fe_MUX19_fun=([](){
		if(!fe_MUX19_bool) op_mux(fe_MUX19_mem,fe_AND46_fun(),fe_REG6_fun(),fe_MUX4_fun(),32);
		fe_MUX19_bool=true;
		return fe_MUX19_mem;
	});
	fe_NOT12_fun=([](){
		if(!fe_NOT12_bool) op_not(fe_NOT12_mem,fe_SELECT11_fun(),1);
		fe_NOT12_bool=true;
		return fe_NOT12_mem;
	});
	fe_AND42_fun=([](){
		if(!fe_AND42_bool) op_and(fe_AND42_mem,fe_AND35_fun(),fe_NOT12_fun(),1);
		fe_AND42_bool=true;
		return fe_AND42_mem;
	});
	fe_AND45_fun=([](){
		if(!fe_AND45_bool) op_and(fe_AND45_mem,fe_AND42_fun(),fe_SELECT13_fun(),1);
		fe_AND45_bool=true;
		return fe_AND45_mem;
	});
	fe_MUX16_fun=([](){
		if(!fe_MUX16_bool) op_mux(fe_MUX16_mem,fe_AND45_fun(),fe_REG5_fun(),fe_MUX4_fun(),32);
		fe_MUX16_bool=true;
		return fe_MUX16_mem;
	});
	fe_NOT13_fun=([](){
		if(!fe_NOT13_bool) op_not(fe_NOT13_mem,fe_SELECT13_fun(),1);
		fe_NOT13_bool=true;
		return fe_NOT13_mem;
	});
	fe_AND44_fun=([](){
		if(!fe_AND44_bool) op_and(fe_AND44_mem,fe_AND42_fun(),fe_NOT13_fun(),1);
		fe_AND44_bool=true;
		return fe_AND44_mem;
	});
	fe_MUX15_fun=([](){
		if(!fe_MUX15_bool) op_mux(fe_MUX15_mem,fe_AND44_fun(),fe_REG4_fun(),fe_MUX4_fun(),32);
		fe_MUX15_bool=true;
		return fe_MUX15_mem;
	});
	fe_NOT8_fun=([](){
		if(!fe_NOT8_bool) op_not(fe_NOT8_mem,fe_SELECT3_fun(),1);
		fe_NOT8_bool=true;
		return fe_NOT8_mem;
	});
	fe_AND34_fun=([](){
		if(!fe_AND34_bool) op_and(fe_AND34_mem,fe_AND32_fun(),fe_NOT8_fun(),1);
		fe_AND34_bool=true;
		return fe_AND34_mem;
	});
	fe_AND37_fun=([](){
		if(!fe_AND37_bool) op_and(fe_AND37_mem,fe_AND34_fun(),fe_SELECT5_fun(),1);
		fe_AND37_bool=true;
		return fe_AND37_mem;
	});
	fe_AND41_fun=([](){
		if(!fe_AND41_bool) op_and(fe_AND41_mem,fe_AND37_fun(),fe_SELECT9_fun(),1);
		fe_AND41_bool=true;
		return fe_AND41_mem;
	});
	fe_MUX10_fun=([](){
		if(!fe_MUX10_bool) op_mux(fe_MUX10_mem,fe_AND41_fun(),fe_REG3_fun(),fe_MUX4_fun(),32);
		fe_MUX10_bool=true;
		return fe_MUX10_mem;
	});
	fe_NOT11_fun=([](){
		if(!fe_NOT11_bool) op_not(fe_NOT11_mem,fe_SELECT9_fun(),1);
		fe_NOT11_bool=true;
		return fe_NOT11_mem;
	});
	fe_AND40_fun=([](){
		if(!fe_AND40_bool) op_and(fe_AND40_mem,fe_AND37_fun(),fe_NOT11_fun(),1);
		fe_AND40_bool=true;
		return fe_AND40_mem;
	});
	fe_MUX9_fun=([](){
		if(!fe_MUX9_bool) op_mux(fe_MUX9_mem,fe_AND40_fun(),fe_REG2_fun(),fe_MUX4_fun(),32);
		fe_MUX9_bool=true;
		return fe_MUX9_mem;
	});
	fe_NOT9_fun=([](){
		if(!fe_NOT9_bool) op_not(fe_NOT9_mem,fe_SELECT5_fun(),1);
		fe_NOT9_bool=true;
		return fe_NOT9_mem;
	});
	fe_AND36_fun=([](){
		if(!fe_AND36_bool) op_and(fe_AND36_mem,fe_AND34_fun(),fe_NOT9_fun(),1);
		fe_AND36_bool=true;
		return fe_AND36_mem;
	});
	fe_AND39_fun=([](){
		if(!fe_AND39_bool) op_and(fe_AND39_mem,fe_AND36_fun(),fe_SELECT7_fun(),1);
		fe_AND39_bool=true;
		return fe_AND39_mem;
	});
	fe_MUX6_fun=([](){
		if(!fe_MUX6_bool) op_mux(fe_MUX6_mem,fe_AND39_fun(),fe_REG1_fun(),fe_MUX4_fun(),32);
		fe_MUX6_bool=true;
		return fe_MUX6_mem;
	});
	fe_NOT10_fun=([](){
		if(!fe_NOT10_bool) op_not(fe_NOT10_mem,fe_SELECT7_fun(),1);
		fe_NOT10_bool=true;
		return fe_NOT10_mem;
	});
	fe_AND38_fun=([](){
		if(!fe_AND38_bool) op_and(fe_AND38_mem,fe_AND36_fun(),fe_NOT10_fun(),1);
		fe_AND38_bool=true;
		return fe_AND38_mem;
	});
	fe_MUX5_fun=([](){
		if(!fe_MUX5_bool) op_mux(fe_MUX5_mem,fe_AND38_fun(),fe_REG0_fun(),fe_MUX4_fun(),32);
		fe_MUX5_bool=true;
		return fe_MUX5_mem;
	});
	fe_0_fun=([](){
		if(!fe_0_bool) copy(fe_MUX50_fun(),fe_0_mem,0,0,32);
		fe_0_bool=true;
		return fe_0_mem;
	});
	fe_AND5_fun=([](){
		if(!fe_AND5_bool) op_and(fe_AND5_mem,fe_NOT2_fun(),fe_SLICE6_fun(),1);
		fe_AND5_bool=true;
		return fe_AND5_mem;
	});
	fe_AND16_fun=([](){
		if(!fe_AND16_bool) op_and(fe_AND16_mem,fe_AND5_fun(),fe_AND8_fun(),1);
		fe_AND16_bool=true;
		return fe_AND16_mem;
	});
	fe_OR5_fun=([](){
		if(!fe_OR5_bool) op_or(fe_OR5_mem,fe_AND16_fun(),fe_AND25_fun(),1);
		fe_OR5_bool=true;
		return fe_OR5_mem;
	});
	fe_CONCAT1_fun=([](){
		if(!fe_CONCAT1_bool) op_concat(fe_CONCAT1_mem,fe_AND13_fun(),fe_OR5_fun(),1,1);
		fe_CONCAT1_bool=true;
		return fe_CONCAT1_mem;
	});
	fe_AND11_fun=([](){
		if(!fe_AND11_bool) op_and(fe_AND11_mem,fe_SLICE8_fun(),fe_SLICE9_fun(),1);
		fe_AND11_bool=true;
		return fe_AND11_mem;
	});
	fe_AND15_fun=([](){
		if(!fe_AND15_bool) op_and(fe_AND15_mem,fe_AND4_fun(),fe_AND11_fun(),1);
		fe_AND15_bool=true;
		return fe_AND15_mem;
	});
	fe_AND14_fun=([](){
		if(!fe_AND14_bool) op_and(fe_AND14_mem,fe_AND4_fun(),fe_AND10_fun(),1);
		fe_AND14_bool=true;
		return fe_AND14_mem;
	});
	fe_CONCAT2_fun=([](){
		if(!fe_CONCAT2_bool) op_concat(fe_CONCAT2_mem,fe_AND15_fun(),fe_AND14_fun(),1,1);
		fe_CONCAT2_bool=true;
		return fe_CONCAT2_mem;
	});
	fe_CONCAT3_fun=([](){
		if(!fe_CONCAT3_bool) op_concat(fe_CONCAT3_mem,fe_CONCAT1_fun(),fe_CONCAT2_fun(),2,2);
		fe_CONCAT3_bool=true;
		return fe_CONCAT3_mem;
	});
	fe_AND19_fun=([](){
		if(!fe_AND19_bool) op_and(fe_AND19_mem,fe_AND5_fun(),fe_AND11_fun(),1);
		fe_AND19_bool=true;
		return fe_AND19_mem;
	});
	fe_AND17_fun=([](){
		if(!fe_AND17_bool) op_and(fe_AND17_mem,fe_AND5_fun(),fe_AND9_fun(),1);
		fe_AND17_bool=true;
		return fe_AND17_mem;
	});
	fe_CONCAT4_fun=([](){
		if(!fe_CONCAT4_bool) op_concat(fe_CONCAT4_mem,fe_AND19_fun(),fe_AND17_fun(),1,1);
		fe_CONCAT4_bool=true;
		return fe_CONCAT4_mem;
	});
	fe_AND18_fun=([](){
		if(!fe_AND18_bool) op_and(fe_AND18_mem,fe_AND5_fun(),fe_AND10_fun(),1);
		fe_AND18_bool=true;
		return fe_AND18_mem;
	});
	fe_OR6_fun=([](){
		if(!fe_OR6_bool) op_or(fe_OR6_mem,fe_AND18_fun(),fe_AND24_fun(),1);
		fe_OR6_bool=true;
		return fe_OR6_mem;
	});
	_my_constant_1__fun=([](){
		if(!_my_constant_1__bool) of_string(_my_constant_1__mem,1,"0");
		_my_constant_1__bool=true;
		return _my_constant_1__mem;
	});
	fe_CONCAT5_fun=([](){
		if(!fe_CONCAT5_bool) op_concat(fe_CONCAT5_mem,fe_OR6_fun(),_my_constant_1__fun(),1,1);
		fe_CONCAT5_bool=true;
		return fe_CONCAT5_mem;
	});
	fe_CONCAT6_fun=([](){
		if(!fe_CONCAT6_bool) op_concat(fe_CONCAT6_mem,fe_CONCAT4_fun(),fe_CONCAT5_fun(),2,2);
		fe_CONCAT6_bool=true;
		return fe_CONCAT6_mem;
	});
	fe_CONCAT7_fun=([](){
		if(!fe_CONCAT7_bool) op_concat(fe_CONCAT7_mem,fe_CONCAT3_fun(),fe_CONCAT6_fun(),4,4);
		fe_CONCAT7_bool=true;
		return fe_CONCAT7_mem;
	});
	fe_AND28_fun=([](){
		if(!fe_AND28_bool) op_and(fe_AND28_mem,fe_AND1_fun(),fe_AND12_fun(),1);
		fe_AND28_bool=true;
		return fe_AND28_mem;
	});
	fe_AND27_fun=([](){
		if(!fe_AND27_bool) op_and(fe_AND27_mem,fe_AND7_fun(),fe_AND11_fun(),1);
		fe_AND27_bool=true;
		return fe_AND27_mem;
	});
	fe_AND6_fun=([](){
		if(!fe_AND6_bool) op_and(fe_AND6_mem,fe_SLICE5_fun(),fe_NOT3_fun(),1);
		fe_AND6_bool=true;
		return fe_AND6_mem;
	});
	fe_AND23_fun=([](){
		if(!fe_AND23_bool) op_and(fe_AND23_mem,fe_AND6_fun(),fe_AND11_fun(),1);
		fe_AND23_bool=true;
		return fe_AND23_mem;
	});
	fe_AND22_fun=([](){
		if(!fe_AND22_bool) op_and(fe_AND22_mem,fe_AND6_fun(),fe_AND10_fun(),1);
		fe_AND22_bool=true;
		return fe_AND22_mem;
	});
	fe_AND21_fun=([](){
		if(!fe_AND21_bool) op_and(fe_AND21_mem,fe_AND6_fun(),fe_AND9_fun(),1);
		fe_AND21_bool=true;
		return fe_AND21_mem;
	});
	fe_AND20_fun=([](){
		if(!fe_AND20_bool) op_and(fe_AND20_mem,fe_AND6_fun(),fe_AND8_fun(),1);
		fe_AND20_bool=true;
		return fe_AND20_mem;
	});
	_my_constant_2__fun=([](){
		if(!_my_constant_2__bool) of_string(_my_constant_2__mem,2,"00");
		_my_constant_2__bool=true;
		return _my_constant_2__mem;
	});


    if(meta)
    {
        initscr();
        start_color();
        init_pair(1,COLOR_GREEN,COLOR_GREEN);
    }
    while(step!=0)
    {
        step--;
        //inputs
		_my_constant_0__bool=false;
		_my_constant_1__bool=false;
		_my_constant_2__bool=false;
		_my_constant_3__bool=false;
		_my_constant_4__bool=false;
		fe_0_bool=false;
		fe_AND0_bool=false;
		fe_AND1_bool=false;
		fe_AND10_bool=false;
		fe_AND11_bool=false;
		fe_AND12_bool=false;
		fe_AND13_bool=false;
		fe_AND14_bool=false;
		fe_AND15_bool=false;
		fe_AND16_bool=false;
		fe_AND17_bool=false;
		fe_AND18_bool=false;
		fe_AND19_bool=false;
		fe_AND2_bool=false;
		fe_AND20_bool=false;
		fe_AND21_bool=false;
		fe_AND22_bool=false;
		fe_AND23_bool=false;
		fe_AND24_bool=false;
		fe_AND25_bool=false;
		fe_AND26_bool=false;
		fe_AND27_bool=false;
		fe_AND28_bool=false;
		fe_AND29_bool=false;
		fe_AND3_bool=false;
		fe_AND30_bool=false;
		fe_AND31_bool=false;
		fe_AND32_bool=false;
		fe_AND33_bool=false;
		fe_AND34_bool=false;
		fe_AND35_bool=false;
		fe_AND36_bool=false;
		fe_AND37_bool=false;
		fe_AND38_bool=false;
		fe_AND39_bool=false;
		fe_AND4_bool=false;
		fe_AND40_bool=false;
		fe_AND41_bool=false;
		fe_AND42_bool=false;
		fe_AND43_bool=false;
		fe_AND44_bool=false;
		fe_AND45_bool=false;
		fe_AND46_bool=false;
		fe_AND47_bool=false;
		fe_AND48_bool=false;
		fe_AND49_bool=false;
		fe_AND5_bool=false;
		fe_AND50_bool=false;
		fe_AND51_bool=false;
		fe_AND52_bool=false;
		fe_AND53_bool=false;
		fe_AND54_bool=false;
		fe_AND55_bool=false;
		fe_AND56_bool=false;
		fe_AND57_bool=false;
		fe_AND58_bool=false;
		fe_AND59_bool=false;
		fe_AND6_bool=false;
		fe_AND60_bool=false;
		fe_AND61_bool=false;
		fe_AND62_bool=false;
		fe_AND63_bool=false;
		fe_AND64_bool=false;
		fe_AND65_bool=false;
		fe_AND66_bool=false;
		fe_AND67_bool=false;
		fe_AND68_bool=false;
		fe_AND69_bool=false;
		fe_AND7_bool=false;
		fe_AND70_bool=false;
		fe_AND71_bool=false;
		fe_AND72_bool=false;
		fe_AND73_bool=false;
		fe_AND74_bool=false;
		fe_AND75_bool=false;
		fe_AND76_bool=false;
		fe_AND77_bool=false;
		fe_AND78_bool=false;
		fe_AND8_bool=false;
		fe_AND9_bool=false;
		fe_CONCAT0_bool=false;
		fe_CONCAT1_bool=false;
		fe_CONCAT10_bool=false;
		fe_CONCAT11_bool=false;
		fe_CONCAT12_bool=false;
		fe_CONCAT13_bool=false;
		fe_CONCAT14_bool=false;
		fe_CONCAT15_bool=false;
		fe_CONCAT16_bool=false;
		fe_CONCAT17_bool=false;
		fe_CONCAT18_bool=false;
		fe_CONCAT19_bool=false;
		fe_CONCAT2_bool=false;
		fe_CONCAT3_bool=false;
		fe_CONCAT4_bool=false;
		fe_CONCAT5_bool=false;
		fe_CONCAT6_bool=false;
		fe_CONCAT7_bool=false;
		fe_CONCAT8_bool=false;
		fe_CONCAT9_bool=false;
		fe_MUX0_bool=false;
		fe_MUX1_bool=false;
		fe_MUX10_bool=false;
		fe_MUX11_bool=false;
		fe_MUX12_bool=false;
		fe_MUX13_bool=false;
		fe_MUX14_bool=false;
		fe_MUX15_bool=false;
		fe_MUX16_bool=false;
		fe_MUX17_bool=false;
		fe_MUX18_bool=false;
		fe_MUX19_bool=false;
		fe_MUX2_bool=false;
		fe_MUX20_bool=false;
		fe_MUX21_bool=false;
		fe_MUX22_bool=false;
		fe_MUX23_bool=false;
		fe_MUX24_bool=false;
		fe_MUX25_bool=false;
		fe_MUX26_bool=false;
		fe_MUX27_bool=false;
		fe_MUX28_bool=false;
		fe_MUX29_bool=false;
		fe_MUX3_bool=false;
		fe_MUX30_bool=false;
		fe_MUX31_bool=false;
		fe_MUX32_bool=false;
		fe_MUX33_bool=false;
		fe_MUX34_bool=false;
		fe_MUX35_bool=false;
		fe_MUX36_bool=false;
		fe_MUX37_bool=false;
		fe_MUX38_bool=false;
		fe_MUX39_bool=false;
		fe_MUX4_bool=false;
		fe_MUX40_bool=false;
		fe_MUX41_bool=false;
		fe_MUX42_bool=false;
		fe_MUX43_bool=false;
		fe_MUX44_bool=false;
		fe_MUX45_bool=false;
		fe_MUX46_bool=false;
		fe_MUX47_bool=false;
		fe_MUX48_bool=false;
		fe_MUX49_bool=false;
		fe_MUX5_bool=false;
		fe_MUX50_bool=false;
		fe_MUX51_bool=false;
		fe_MUX6_bool=false;
		fe_MUX7_bool=false;
		fe_MUX8_bool=false;
		fe_MUX9_bool=false;
		fe_NOT0_bool=false;
		fe_NOT1_bool=false;
		fe_NOT10_bool=false;
		fe_NOT11_bool=false;
		fe_NOT12_bool=false;
		fe_NOT13_bool=false;
		fe_NOT14_bool=false;
		fe_NOT15_bool=false;
		fe_NOT16_bool=false;
		fe_NOT17_bool=false;
		fe_NOT18_bool=false;
		fe_NOT19_bool=false;
		fe_NOT2_bool=false;
		fe_NOT20_bool=false;
		fe_NOT21_bool=false;
		fe_NOT22_bool=false;
		fe_NOT3_bool=false;
		fe_NOT4_bool=false;
		fe_NOT5_bool=false;
		fe_NOT6_bool=false;
		fe_NOT7_bool=false;
		fe_NOT8_bool=false;
		fe_NOT9_bool=false;
		fe_OR0_bool=false;
		fe_OR1_bool=false;
		fe_OR10_bool=false;
		fe_OR11_bool=false;
		fe_OR2_bool=false;
		fe_OR3_bool=false;
		fe_OR4_bool=false;
		fe_OR5_bool=false;
		fe_OR6_bool=false;
		fe_OR7_bool=false;
		fe_OR8_bool=false;
		fe_OR9_bool=false;
		fe_RAM0_bool=false;
		fe_REG0_bool=false;
		fe_REG1_bool=false;
		fe_REG10_bool=false;
		fe_REG11_bool=false;
		fe_REG12_bool=false;
		fe_REG13_bool=false;
		fe_REG14_bool=false;
		fe_REG15_bool=false;
		fe_REG16_bool=false;
		fe_REG17_bool=false;
		fe_REG2_bool=false;
		fe_REG3_bool=false;
		fe_REG4_bool=false;
		fe_REG5_bool=false;
		fe_REG6_bool=false;
		fe_REG7_bool=false;
		fe_REG8_bool=false;
		fe_REG9_bool=false;
		fe_ROM0_bool=false;
		fe_SELECT0_bool=false;
		fe_SELECT1_bool=false;
		fe_SELECT10_bool=false;
		fe_SELECT11_bool=false;
		fe_SELECT12_bool=false;
		fe_SELECT13_bool=false;
		fe_SELECT14_bool=false;
		fe_SELECT15_bool=false;
		fe_SELECT16_bool=false;
		fe_SELECT17_bool=false;
		fe_SELECT18_bool=false;
		fe_SELECT19_bool=false;
		fe_SELECT2_bool=false;
		fe_SELECT20_bool=false;
		fe_SELECT21_bool=false;
		fe_SELECT22_bool=false;
		fe_SELECT23_bool=false;
		fe_SELECT24_bool=false;
		fe_SELECT25_bool=false;
		fe_SELECT26_bool=false;
		fe_SELECT27_bool=false;
		fe_SELECT28_bool=false;
		fe_SELECT29_bool=false;
		fe_SELECT3_bool=false;
		fe_SELECT30_bool=false;
		fe_SELECT31_bool=false;
		fe_SELECT32_bool=false;
		fe_SELECT33_bool=false;
		fe_SELECT34_bool=false;
		fe_SELECT35_bool=false;
		fe_SELECT36_bool=false;
		fe_SELECT37_bool=false;
		fe_SELECT38_bool=false;
		fe_SELECT39_bool=false;
		fe_SELECT4_bool=false;
		fe_SELECT40_bool=false;
		fe_SELECT41_bool=false;
		fe_SELECT42_bool=false;
		fe_SELECT43_bool=false;
		fe_SELECT44_bool=false;
		fe_SELECT5_bool=false;
		fe_SELECT6_bool=false;
		fe_SELECT7_bool=false;
		fe_SELECT8_bool=false;
		fe_SELECT9_bool=false;
		fe_SLICE0_bool=false;
		fe_SLICE1_bool=false;
		fe_SLICE10_bool=false;
		fe_SLICE11_bool=false;
		fe_SLICE12_bool=false;
		fe_SLICE13_bool=false;
		fe_SLICE14_bool=false;
		fe_SLICE15_bool=false;
		fe_SLICE2_bool=false;
		fe_SLICE3_bool=false;
		fe_SLICE4_bool=false;
		fe_SLICE5_bool=false;
		fe_SLICE6_bool=false;
		fe_SLICE7_bool=false;
		fe_SLICE8_bool=false;
		fe_SLICE9_bool=false;
		fe_XOR0_bool=false;
		fe_XOR1_bool=false;
		fe_XOR10_bool=false;
		fe_XOR11_bool=false;
		fe_XOR12_bool=false;
		fe_XOR2_bool=false;
		fe_XOR3_bool=false;
		fe_XOR4_bool=false;
		fe_XOR5_bool=false;
		fe_XOR6_bool=false;
		fe_XOR7_bool=false;
		fe_XOR8_bool=false;
		fe_XOR9_bool=false;


        //actualisation des rams
		if(*fe_AND28_fun()){
			copy(fe_MUX4_fun(),fe_RAM0_ram,0,to_int(fe_SLICE14_fun(),0,13),32);
		}


        //outputs


        if(meta)
        {
            if(clock!=time(0))
            {
                clock=time(0);
                of_int(clock_registre,0,reg_size,clock);
            }

            int disp=to_int(display,0,reg_size);
            if(disp!=0)
            {
                for(int i=0;i<14;i++)
                {   
                    clock_data[i]=int(
                        (to_int(ram,
                        (disp&((1<<ram_size_addr)-1))+i,//on selectionne les derniers bits pour l'adresse
                        ram_size_word))
                        &((1<<7)-1));//7 bits d'information
                }
                horloge(Coord(9,9),clock_data);
                of_int(display,0,reg_size,0);
            }
        }

        //actualisation des registres
		copy(fe_MUX51_fun(),fe_MUX51_reg,0,0,13);
		copy(_my_constant_2__fun(),_my_constant_2__reg,0,0,2);
		copy(fe_MUX5_fun(),fe_MUX5_reg,0,0,32);
		copy(fe_MUX6_fun(),fe_MUX6_reg,0,0,32);
		copy(fe_MUX9_fun(),fe_MUX9_reg,0,0,32);
		copy(fe_MUX10_fun(),fe_MUX10_reg,0,0,32);
		copy(fe_MUX15_fun(),fe_MUX15_reg,0,0,32);
		copy(fe_MUX16_fun(),fe_MUX16_reg,0,0,32);
		copy(fe_MUX19_fun(),fe_MUX19_reg,0,0,32);
		copy(fe_MUX20_fun(),fe_MUX20_reg,0,0,32);
		copy(fe_MUX27_fun(),fe_MUX27_reg,0,0,32);
		copy(fe_MUX28_fun(),fe_MUX28_reg,0,0,32);
		copy(fe_MUX31_fun(),fe_MUX31_reg,0,0,32);
		copy(fe_MUX32_fun(),fe_MUX32_reg,0,0,32);
		copy(fe_MUX37_fun(),fe_MUX37_reg,0,0,32);
		copy(fe_MUX38_fun(),fe_MUX38_reg,0,0,32);
		copy(fe_MUX41_fun(),fe_MUX41_reg,0,0,32);
		copy(fe_MUX42_fun(),fe_MUX42_reg,0,0,32);

        if(meta)
        {
            refresh();
        }

    }

    if(meta) endwin();
}

bool get_bit(char *mem,int no)
{
    int i=no/8;
    int k=no%8;
    char mask=1<<k;
    return mem[i] & mask;
}

void set_bit(char *mem,int no,bool val)
{
    int i=no/8;
    int k=no%8;
    char mask0=~(1<<k);
    mem[i]=mem[i]&mask0;
    char mask=val<<k;
    mem[i]=mem[i]|mask;
}

void copy(char *src,char *dest,int src_addr,int dest_addr,int word_size)
{
    for(int i=0;i<word_size;i++)
    {
        set_bit(dest,dest_addr*word_size+i,get_bit(src,src_addr*word_size+i));
    }
}

void create_mem(char **mem,int addr_size,int word_size)
{
    int size=((1<<addr_size)*word_size+7)/8;
    *mem=new char[size];
    for(int i=0;i<size;i++)
    {
        (*mem)[i]=0;
    }
}

int to_int(char *mem,int addr,int word_size)
{
    int ret=0;
    for(int i=0;i<word_size;i++)
    {
        ret*=2;
        ret+=get_bit(mem,addr*word_size+i);
    }
    return ret;
}

void of_int(char *mem,int addr,int word_size,int i)
{
    for(int k=word_size-1;k>=0;k--)
    {
        set_bit(mem,addr*word_size+k,i%2);
        i/=2;
    }
}

void print(char *mem,int addr,int word_size,bool meta)
{
    if(meta) move(0,0);
    for(int i=0;i<word_size;i++)
    {
        if(meta)
            printw("%d",get_bit(mem,addr*word_size+i));
        else
            cout<<get_bit(mem,addr*word_size+i);
    }
    if(!meta) cout<<endl;
}

bool of_input(char *mem,int size,string mem_name)
{
    cout<<mem_name<<"?"<<endl;
    string str;
    cin>>str;
    if(size!=str.size())
    {
        cerr<<"mauvais format"<<endl;
        return false;
    }            
    for(int i=0;i<size;i++)
    {
        if(str[i]=='0'||str[i]=='1')
        {
            str[i]-='0';
            set_bit(mem,i,str[i]);
        }
        else
        {
            cerr<<"mauvais format"<<endl;
            return false;
        }
    }
    return true;
}

void of_string(char *mem,int size,string str)
{
    for(int i=0;i<size;i++)
    {
        str[i]-='0';
        set_bit(mem,i,str[i]);
    }
}

void init_rom(char *rom,char* filename,bool hexa,int addr_size,int word_size)
{
    ifstream file(filename);
    if(!file)
    {
        cerr<<"erreur lors de l'ouverture du fichiers "<<filename<<endl;
        exit(EXIT_FAILURE);
    }

    char buff;
    int nb_bits;
    int size=(1<<addr_size)*word_size;
    if(hexa)
    {
        nb_bits=4;
        if(size%4!=0)
        {
            cerr<<"format hexadecimal impossible car la taille de la rom n'est pas multiple de 4"<<endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        nb_bits=1;
    }
    int pos=0;
    while(file.get(buff)&&pos<size)
    {
        if(hexa)
        {
            if('0'<=buff && buff <= '9')
                buff-='0';
            else if ('A'<=buff && buff <='F')
                buff+=10-'A';
            else if ('a'<=buff && buff <= 'f')
                buff+=10-'a';
            else
                continue;
        }
        else
        {
            if(buff=='0' || buff=='1')
                buff-='0';
            else
                continue;
        }
        pos+=nb_bits;
        for(int i=1;i<=nb_bits;i++)
        {
            set_bit(rom,pos-i,buff%2);
            buff=buff>>1;
        }
    }
    file.close();
}

void op_not(char *left,char* right,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=~right[i];
    }
}

void op_and(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=a[i]&b[i];
    }
}

void op_nand(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=~(a[i]&b[i]);
    }
}

void op_or(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=(a[i]|b[i]);
    }
}

void op_xor(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=(a[i]^b[i]);
    }
}

void op_concat(char *left,char* a,char* b,int a_size,int b_size)
{
    for(int i=0;i<a_size;i++)
    {
        set_bit(left,i,get_bit(a,i));
    }

    for(int i=0;i<b_size;i++)
    {
        set_bit(left,i+a_size,get_bit(b,i));
    }
}

void op_select(char *left,int i,char *a)
{
    set_bit(left,0,get_bit(a,i));
}

void op_mux(char* left,char* choice,char *a,char *b,int size)
{
    if(!get_bit(choice,0))
        copy(a,left,0,0,size);
    else
        copy(b,left,0,0,size);
}

void op_slice(char* left,int i1,int i2,char *a)
{
    for(int i=0;i<i2-i1+1;i++)
    {
        set_bit(left,i,get_bit(a,i+i1));
    }
}

//l'horloge
Coord operator+(Coord const& a,Coord const& b)
{
    return Coord(a.x+b.x,a.y+b.y);
}

Coord operator*(double const& a,Coord const& b)
{
    return Coord(a*b.x,a*b.y);
}

Coord operator-(Coord const& a,Coord const& b)
{
    return a+(-1)*b;
}

void setPixel(Coord pos)
{
    mvaddch(int(pos.x),int(2*pos.y),' '|COLOR_PAIR(1));    
    mvaddch(int(pos.x),int(2*pos.y+1),' '|COLOR_PAIR(1));    
}

void segment(Coord a,Coord b)
{
    Coord vect;
    Coord dir(b.x-a.x,b.y-a.y);
    Coord pos=a;
    double norm(sqrt(dir.x*dir.x+dir.y*dir.y));
    dir.x/=norm;
    dir.y/=norm;
    while(norm>0.9)
    {
        setPixel(pos);

        pos=pos+dir;

        vect=b-pos;

        norm=vect.x*vect.x+vect.y*vect.y;
    }
    setPixel(pos);
}

void afficheur(Coord pos,char val)
{
    for(int i=0;i<7;i++)
    {
        if(val%2)
        {
            segment(segments[i][0]+pos,segments[i][1]+pos);
        }
        val/=2;
    }
}

void horloge(Coord pos,char* data)
{
    Coord curr_pos=pos+Coord(0,10);

    for(int i=0;i<3;i++)
    {
        afficheur(curr_pos,data[2*i]);
        curr_pos=curr_pos+Coord(0,7);
        afficheur(curr_pos,data[2*i+1]);
        curr_pos=curr_pos+Coord(0,7);
        if(i!=2)
        {
            setPixel(curr_pos+Coord(3,0));
            setPixel(curr_pos+Coord(7,0));
            curr_pos=curr_pos+Coord(0,2);
        }
    }

    curr_pos=pos+Coord(13,0);
    for(int i=3;i<6;i++)
    {
        afficheur(curr_pos,data[2*i]);
        curr_pos=curr_pos+Coord(0,7);
        afficheur(curr_pos,data[2*i+1]);
        curr_pos=curr_pos+Coord(0,7);
        if(i==5)
        {
            i++;
            afficheur(curr_pos,data[2*i]);
            curr_pos=curr_pos+Coord(0,7);
            afficheur(curr_pos,data[2*i+1]);
            curr_pos=curr_pos+Coord(0,7);
        }
        else
        {
            segment(curr_pos+Coord(9,0),curr_pos+Coord(1,3));            
            curr_pos=curr_pos+Coord(0,5);
        }
    }
    mvaddch(LINES-1,COLS-1,' ');
}