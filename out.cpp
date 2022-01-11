#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

bool get_bit(char *mem,int no);

void set_bit(char *mem,int no,bool val);

void copy(char *src,char *dest,int src_addr,int dest_addr,int word_size);

void create_mem(char **mem,int addr_size,int word_size);

int to_int(char *mem,int addr,int word_size);

void print(char *mem,int addr,int word_size);

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

//déclaration des variables
char* fe_ROM0_rom;
char* fe_0_mem;
bool fe_0_bool;
function<char*()> fe_0;
char* fe_AND0_mem;
bool fe_AND0_bool;
function<char*()> fe_AND0;
char* fe_AND1_mem;
bool fe_AND1_bool;
function<char*()> fe_AND1;
char* fe_AND10_mem;
bool fe_AND10_bool;
function<char*()> fe_AND10;
char* fe_AND11_mem;
bool fe_AND11_bool;
function<char*()> fe_AND11;
char* fe_AND12_mem;
bool fe_AND12_bool;
function<char*()> fe_AND12;
char* fe_AND13_mem;
bool fe_AND13_bool;
function<char*()> fe_AND13;
char* fe_AND14_mem;
bool fe_AND14_bool;
function<char*()> fe_AND14;
char* fe_AND15_mem;
bool fe_AND15_bool;
function<char*()> fe_AND15;
char* fe_AND16_mem;
bool fe_AND16_bool;
function<char*()> fe_AND16;
char* fe_AND17_mem;
bool fe_AND17_bool;
function<char*()> fe_AND17;
char* fe_AND18_mem;
bool fe_AND18_bool;
function<char*()> fe_AND18;
char* fe_AND19_mem;
bool fe_AND19_bool;
function<char*()> fe_AND19;
char* fe_AND2_mem;
bool fe_AND2_bool;
function<char*()> fe_AND2;
char* fe_AND20_mem;
bool fe_AND20_bool;
function<char*()> fe_AND20;
char* fe_AND21_mem;
bool fe_AND21_bool;
function<char*()> fe_AND21;
char* fe_AND22_mem;
bool fe_AND22_bool;
function<char*()> fe_AND22;
char* fe_AND23_mem;
bool fe_AND23_bool;
function<char*()> fe_AND23;
char* fe_AND24_mem;
bool fe_AND24_bool;
function<char*()> fe_AND24;
char* fe_AND25_mem;
bool fe_AND25_bool;
function<char*()> fe_AND25;
char* fe_AND26_mem;
bool fe_AND26_bool;
function<char*()> fe_AND26;
char* fe_AND27_mem;
bool fe_AND27_bool;
function<char*()> fe_AND27;
char* fe_AND28_mem;
bool fe_AND28_bool;
function<char*()> fe_AND28;
char* fe_AND29_mem;
bool fe_AND29_bool;
function<char*()> fe_AND29;
char* fe_AND3_mem;
bool fe_AND3_bool;
function<char*()> fe_AND3;
char* fe_AND30_mem;
bool fe_AND30_bool;
function<char*()> fe_AND30;
char* fe_AND31_mem;
bool fe_AND31_bool;
function<char*()> fe_AND31;
char* fe_AND32_mem;
bool fe_AND32_bool;
function<char*()> fe_AND32;
char* fe_AND33_mem;
bool fe_AND33_bool;
function<char*()> fe_AND33;
char* fe_AND34_mem;
bool fe_AND34_bool;
function<char*()> fe_AND34;
char* fe_AND35_mem;
bool fe_AND35_bool;
function<char*()> fe_AND35;
char* fe_AND36_mem;
bool fe_AND36_bool;
function<char*()> fe_AND36;
char* fe_AND37_mem;
bool fe_AND37_bool;
function<char*()> fe_AND37;
char* fe_AND38_mem;
bool fe_AND38_bool;
function<char*()> fe_AND38;
char* fe_AND39_mem;
bool fe_AND39_bool;
function<char*()> fe_AND39;
char* fe_AND4_mem;
bool fe_AND4_bool;
function<char*()> fe_AND4;
char* fe_AND40_mem;
bool fe_AND40_bool;
function<char*()> fe_AND40;
char* fe_AND41_mem;
bool fe_AND41_bool;
function<char*()> fe_AND41;
char* fe_AND42_mem;
bool fe_AND42_bool;
function<char*()> fe_AND42;
char* fe_AND43_mem;
bool fe_AND43_bool;
function<char*()> fe_AND43;
char* fe_AND44_mem;
bool fe_AND44_bool;
function<char*()> fe_AND44;
char* fe_AND45_mem;
bool fe_AND45_bool;
function<char*()> fe_AND45;
char* fe_AND46_mem;
bool fe_AND46_bool;
function<char*()> fe_AND46;
char* fe_AND47_mem;
bool fe_AND47_bool;
function<char*()> fe_AND47;
char* fe_AND48_mem;
bool fe_AND48_bool;
function<char*()> fe_AND48;
char* fe_AND49_mem;
bool fe_AND49_bool;
function<char*()> fe_AND49;
char* fe_AND5_mem;
bool fe_AND5_bool;
function<char*()> fe_AND5;
char* fe_AND50_mem;
bool fe_AND50_bool;
function<char*()> fe_AND50;
char* fe_AND51_mem;
bool fe_AND51_bool;
function<char*()> fe_AND51;
char* fe_AND52_mem;
bool fe_AND52_bool;
function<char*()> fe_AND52;
char* fe_AND53_mem;
bool fe_AND53_bool;
function<char*()> fe_AND53;
char* fe_AND54_mem;
bool fe_AND54_bool;
function<char*()> fe_AND54;
char* fe_AND55_mem;
bool fe_AND55_bool;
function<char*()> fe_AND55;
char* fe_AND56_mem;
bool fe_AND56_bool;
function<char*()> fe_AND56;
char* fe_AND57_mem;
bool fe_AND57_bool;
function<char*()> fe_AND57;
char* fe_AND58_mem;
bool fe_AND58_bool;
function<char*()> fe_AND58;
char* fe_AND59_mem;
bool fe_AND59_bool;
function<char*()> fe_AND59;
char* fe_AND6_mem;
bool fe_AND6_bool;
function<char*()> fe_AND6;
char* fe_AND60_mem;
bool fe_AND60_bool;
function<char*()> fe_AND60;
char* fe_AND61_mem;
bool fe_AND61_bool;
function<char*()> fe_AND61;
char* fe_AND62_mem;
bool fe_AND62_bool;
function<char*()> fe_AND62;
char* fe_AND63_mem;
bool fe_AND63_bool;
function<char*()> fe_AND63;
char* fe_AND64_mem;
bool fe_AND64_bool;
function<char*()> fe_AND64;
char* fe_AND65_mem;
bool fe_AND65_bool;
function<char*()> fe_AND65;
char* fe_AND66_mem;
bool fe_AND66_bool;
function<char*()> fe_AND66;
char* fe_AND67_mem;
bool fe_AND67_bool;
function<char*()> fe_AND67;
char* fe_AND68_mem;
bool fe_AND68_bool;
function<char*()> fe_AND68;
char* fe_AND69_mem;
bool fe_AND69_bool;
function<char*()> fe_AND69;
char* fe_AND7_mem;
bool fe_AND7_bool;
function<char*()> fe_AND7;
char* fe_AND70_mem;
bool fe_AND70_bool;
function<char*()> fe_AND70;
char* fe_AND71_mem;
bool fe_AND71_bool;
function<char*()> fe_AND71;
char* fe_AND72_mem;
bool fe_AND72_bool;
function<char*()> fe_AND72;
char* fe_AND73_mem;
bool fe_AND73_bool;
function<char*()> fe_AND73;
char* fe_AND74_mem;
bool fe_AND74_bool;
function<char*()> fe_AND74;
char* fe_AND75_mem;
bool fe_AND75_bool;
function<char*()> fe_AND75;
char* fe_AND76_mem;
bool fe_AND76_bool;
function<char*()> fe_AND76;
char* fe_AND77_mem;
bool fe_AND77_bool;
function<char*()> fe_AND77;
char* fe_AND8_mem;
bool fe_AND8_bool;
function<char*()> fe_AND8;
char* fe_AND9_mem;
bool fe_AND9_bool;
function<char*()> fe_AND9;
char* fe_CONCAT0_mem;
bool fe_CONCAT0_bool;
function<char*()> fe_CONCAT0;
char* fe_CONCAT1_mem;
bool fe_CONCAT1_bool;
function<char*()> fe_CONCAT1;
char* fe_CONCAT10_mem;
bool fe_CONCAT10_bool;
function<char*()> fe_CONCAT10;
char* fe_CONCAT11_mem;
bool fe_CONCAT11_bool;
function<char*()> fe_CONCAT11;
char* fe_CONCAT12_mem;
bool fe_CONCAT12_bool;
function<char*()> fe_CONCAT12;
char* fe_CONCAT13_mem;
bool fe_CONCAT13_bool;
function<char*()> fe_CONCAT13;
char* fe_CONCAT14_mem;
bool fe_CONCAT14_bool;
function<char*()> fe_CONCAT14;
char* fe_CONCAT15_mem;
bool fe_CONCAT15_bool;
function<char*()> fe_CONCAT15;
char* fe_CONCAT16_mem;
bool fe_CONCAT16_bool;
function<char*()> fe_CONCAT16;
char* fe_CONCAT17_mem;
bool fe_CONCAT17_bool;
function<char*()> fe_CONCAT17;
char* fe_CONCAT18_mem;
bool fe_CONCAT18_bool;
function<char*()> fe_CONCAT18;
char* fe_CONCAT19_mem;
bool fe_CONCAT19_bool;
function<char*()> fe_CONCAT19;
char* fe_CONCAT2_mem;
bool fe_CONCAT2_bool;
function<char*()> fe_CONCAT2;
char* fe_CONCAT3_mem;
bool fe_CONCAT3_bool;
function<char*()> fe_CONCAT3;
char* fe_CONCAT4_mem;
bool fe_CONCAT4_bool;
function<char*()> fe_CONCAT4;
char* fe_CONCAT5_mem;
bool fe_CONCAT5_bool;
function<char*()> fe_CONCAT5;
char* fe_CONCAT6_mem;
bool fe_CONCAT6_bool;
function<char*()> fe_CONCAT6;
char* fe_CONCAT7_mem;
bool fe_CONCAT7_bool;
function<char*()> fe_CONCAT7;
char* fe_CONCAT8_mem;
bool fe_CONCAT8_bool;
function<char*()> fe_CONCAT8;
char* fe_CONCAT9_mem;
bool fe_CONCAT9_bool;
function<char*()> fe_CONCAT9;
char* fe_MUX1_mem;
bool fe_MUX1_bool;
function<char*()> fe_MUX1;
char* fe_MUX10_mem;
bool fe_MUX10_bool;
function<char*()> fe_MUX10;
char* fe_MUX11_mem;
bool fe_MUX11_bool;
function<char*()> fe_MUX11;
char* fe_MUX12_mem;
bool fe_MUX12_bool;
function<char*()> fe_MUX12;
char* fe_MUX13_mem;
bool fe_MUX13_bool;
function<char*()> fe_MUX13;
char* fe_MUX14_mem;
bool fe_MUX14_bool;
function<char*()> fe_MUX14;
char* fe_MUX15_mem;
bool fe_MUX15_bool;
function<char*()> fe_MUX15;
char* fe_MUX16_mem;
bool fe_MUX16_bool;
function<char*()> fe_MUX16;
char* fe_MUX17_mem;
bool fe_MUX17_bool;
function<char*()> fe_MUX17;
char* fe_MUX18_mem;
bool fe_MUX18_bool;
function<char*()> fe_MUX18;
char* fe_MUX19_mem;
bool fe_MUX19_bool;
function<char*()> fe_MUX19;
char* fe_MUX2_mem;
bool fe_MUX2_bool;
function<char*()> fe_MUX2;
char* fe_MUX20_mem;
bool fe_MUX20_bool;
function<char*()> fe_MUX20;
char* fe_MUX21_mem;
bool fe_MUX21_bool;
function<char*()> fe_MUX21;
char* fe_MUX22_mem;
bool fe_MUX22_bool;
function<char*()> fe_MUX22;
char* fe_MUX23_mem;
bool fe_MUX23_bool;
function<char*()> fe_MUX23;
char* fe_MUX24_mem;
bool fe_MUX24_bool;
function<char*()> fe_MUX24;
char* fe_MUX25_mem;
bool fe_MUX25_bool;
function<char*()> fe_MUX25;
char* fe_MUX26_mem;
bool fe_MUX26_bool;
function<char*()> fe_MUX26;
char* fe_MUX27_mem;
bool fe_MUX27_bool;
function<char*()> fe_MUX27;
char* fe_MUX28_mem;
bool fe_MUX28_bool;
function<char*()> fe_MUX28;
char* fe_MUX29_mem;
bool fe_MUX29_bool;
function<char*()> fe_MUX29;
char* fe_MUX3_mem;
bool fe_MUX3_bool;
function<char*()> fe_MUX3;
char* fe_MUX30_mem;
bool fe_MUX30_bool;
function<char*()> fe_MUX30;
char* fe_MUX31_mem;
bool fe_MUX31_bool;
function<char*()> fe_MUX31;
char* fe_MUX32_mem;
bool fe_MUX32_bool;
function<char*()> fe_MUX32;
char* fe_MUX33_mem;
bool fe_MUX33_bool;
function<char*()> fe_MUX33;
char* fe_MUX34_mem;
bool fe_MUX34_bool;
function<char*()> fe_MUX34;
char* fe_MUX35_mem;
bool fe_MUX35_bool;
function<char*()> fe_MUX35;
char* fe_MUX36_mem;
bool fe_MUX36_bool;
function<char*()> fe_MUX36;
char* fe_MUX37_mem;
bool fe_MUX37_bool;
function<char*()> fe_MUX37;
char* fe_MUX38_mem;
bool fe_MUX38_bool;
function<char*()> fe_MUX38;
char* fe_MUX39_mem;
bool fe_MUX39_bool;
function<char*()> fe_MUX39;
char* fe_MUX4_mem;
bool fe_MUX4_bool;
function<char*()> fe_MUX4;
char* fe_MUX40_mem;
bool fe_MUX40_bool;
function<char*()> fe_MUX40;
char* fe_MUX41_mem;
bool fe_MUX41_bool;
function<char*()> fe_MUX41;
char* fe_MUX42_mem;
bool fe_MUX42_bool;
function<char*()> fe_MUX42;
char* fe_MUX43_mem;
bool fe_MUX43_bool;
function<char*()> fe_MUX43;
char* fe_MUX44_mem;
bool fe_MUX44_bool;
function<char*()> fe_MUX44;
char* fe_MUX45_mem;
bool fe_MUX45_bool;
function<char*()> fe_MUX45;
char* fe_MUX46_mem;
bool fe_MUX46_bool;
function<char*()> fe_MUX46;
char* fe_MUX47_mem;
bool fe_MUX47_bool;
function<char*()> fe_MUX47;
char* fe_MUX48_mem;
bool fe_MUX48_bool;
function<char*()> fe_MUX48;
char* fe_MUX49_mem;
bool fe_MUX49_bool;
function<char*()> fe_MUX49;
char* fe_MUX5_mem;
bool fe_MUX5_bool;
function<char*()> fe_MUX5;
char* fe_MUX50_mem;
bool fe_MUX50_bool;
function<char*()> fe_MUX50;
char* fe_MUX51_mem;
bool fe_MUX51_bool;
function<char*()> fe_MUX51;
char* fe_MUX6_mem;
bool fe_MUX6_bool;
function<char*()> fe_MUX6;
char* fe_MUX7_mem;
bool fe_MUX7_bool;
function<char*()> fe_MUX7;
char* fe_MUX8_mem;
bool fe_MUX8_bool;
function<char*()> fe_MUX8;
char* fe_MUX9_mem;
bool fe_MUX9_bool;
function<char*()> fe_MUX9;
char* fe_NOT0_mem;
bool fe_NOT0_bool;
function<char*()> fe_NOT0;
char* fe_NOT1_mem;
bool fe_NOT1_bool;
function<char*()> fe_NOT1;
char* fe_NOT10_mem;
bool fe_NOT10_bool;
function<char*()> fe_NOT10;
char* fe_NOT11_mem;
bool fe_NOT11_bool;
function<char*()> fe_NOT11;
char* fe_NOT12_mem;
bool fe_NOT12_bool;
function<char*()> fe_NOT12;
char* fe_NOT13_mem;
bool fe_NOT13_bool;
function<char*()> fe_NOT13;
char* fe_NOT14_mem;
bool fe_NOT14_bool;
function<char*()> fe_NOT14;
char* fe_NOT15_mem;
bool fe_NOT15_bool;
function<char*()> fe_NOT15;
char* fe_NOT16_mem;
bool fe_NOT16_bool;
function<char*()> fe_NOT16;
char* fe_NOT17_mem;
bool fe_NOT17_bool;
function<char*()> fe_NOT17;
char* fe_NOT18_mem;
bool fe_NOT18_bool;
function<char*()> fe_NOT18;
char* fe_NOT19_mem;
bool fe_NOT19_bool;
function<char*()> fe_NOT19;
char* fe_NOT2_mem;
bool fe_NOT2_bool;
function<char*()> fe_NOT2;
char* fe_NOT20_mem;
bool fe_NOT20_bool;
function<char*()> fe_NOT20;
char* fe_NOT21_mem;
bool fe_NOT21_bool;
function<char*()> fe_NOT21;
char* fe_NOT22_mem;
bool fe_NOT22_bool;
function<char*()> fe_NOT22;
char* fe_NOT3_mem;
bool fe_NOT3_bool;
function<char*()> fe_NOT3;
char* fe_NOT4_mem;
bool fe_NOT4_bool;
function<char*()> fe_NOT4;
char* fe_NOT5_mem;
bool fe_NOT5_bool;
function<char*()> fe_NOT5;
char* fe_NOT6_mem;
bool fe_NOT6_bool;
function<char*()> fe_NOT6;
char* fe_NOT7_mem;
bool fe_NOT7_bool;
function<char*()> fe_NOT7;
char* fe_NOT8_mem;
bool fe_NOT8_bool;
function<char*()> fe_NOT8;
char* fe_NOT9_mem;
bool fe_NOT9_bool;
function<char*()> fe_NOT9;
char* fe_OR0_mem;
bool fe_OR0_bool;
function<char*()> fe_OR0;
char* fe_OR1_mem;
bool fe_OR1_bool;
function<char*()> fe_OR1;
char* fe_OR10_mem;
bool fe_OR10_bool;
function<char*()> fe_OR10;
char* fe_OR11_mem;
bool fe_OR11_bool;
function<char*()> fe_OR11;
char* fe_OR2_mem;
bool fe_OR2_bool;
function<char*()> fe_OR2;
char* fe_OR3_mem;
bool fe_OR3_bool;
function<char*()> fe_OR3;
char* fe_OR4_mem;
bool fe_OR4_bool;
function<char*()> fe_OR4;
char* fe_OR5_mem;
bool fe_OR5_bool;
function<char*()> fe_OR5;
char* fe_OR6_mem;
bool fe_OR6_bool;
function<char*()> fe_OR6;
char* fe_OR7_mem;
bool fe_OR7_bool;
function<char*()> fe_OR7;
char* fe_OR8_mem;
bool fe_OR8_bool;
function<char*()> fe_OR8;
char* fe_OR9_mem;
bool fe_OR9_bool;
function<char*()> fe_OR9;
char* fe_RAM0_mem;
bool fe_RAM0_bool;
function<char*()> fe_RAM0;
char* fe_REG0_mem;
bool fe_REG0_bool;
function<char*()> fe_REG0;
char* fe_REG1_mem;
bool fe_REG1_bool;
function<char*()> fe_REG1;
char* fe_REG10_mem;
bool fe_REG10_bool;
function<char*()> fe_REG10;
char* fe_REG11_mem;
bool fe_REG11_bool;
function<char*()> fe_REG11;
char* fe_REG12_mem;
bool fe_REG12_bool;
function<char*()> fe_REG12;
char* fe_REG13_mem;
bool fe_REG13_bool;
function<char*()> fe_REG13;
char* fe_REG14_mem;
bool fe_REG14_bool;
function<char*()> fe_REG14;
char* fe_REG15_mem;
bool fe_REG15_bool;
function<char*()> fe_REG15;
char* fe_REG16_mem;
bool fe_REG16_bool;
function<char*()> fe_REG16;
char* fe_REG17_mem;
bool fe_REG17_bool;
function<char*()> fe_REG17;
char* fe_REG2_mem;
bool fe_REG2_bool;
function<char*()> fe_REG2;
char* fe_REG3_mem;
bool fe_REG3_bool;
function<char*()> fe_REG3;
char* fe_REG4_mem;
bool fe_REG4_bool;
function<char*()> fe_REG4;
char* fe_REG5_mem;
bool fe_REG5_bool;
function<char*()> fe_REG5;
char* fe_REG6_mem;
bool fe_REG6_bool;
function<char*()> fe_REG6;
char* fe_REG7_mem;
bool fe_REG7_bool;
function<char*()> fe_REG7;
char* fe_REG8_mem;
bool fe_REG8_bool;
function<char*()> fe_REG8;
char* fe_REG9_mem;
bool fe_REG9_bool;
function<char*()> fe_REG9;
char* fe_ROM0_mem;
bool fe_ROM0_bool;
function<char*()> fe_ROM0;
char* fe_SELECT0_mem;
bool fe_SELECT0_bool;
function<char*()> fe_SELECT0;
char* fe_SELECT1_mem;
bool fe_SELECT1_bool;
function<char*()> fe_SELECT1;
char* fe_SELECT10_mem;
bool fe_SELECT10_bool;
function<char*()> fe_SELECT10;
char* fe_SELECT11_mem;
bool fe_SELECT11_bool;
function<char*()> fe_SELECT11;
char* fe_SELECT12_mem;
bool fe_SELECT12_bool;
function<char*()> fe_SELECT12;
char* fe_SELECT13_mem;
bool fe_SELECT13_bool;
function<char*()> fe_SELECT13;
char* fe_SELECT14_mem;
bool fe_SELECT14_bool;
function<char*()> fe_SELECT14;
char* fe_SELECT15_mem;
bool fe_SELECT15_bool;
function<char*()> fe_SELECT15;
char* fe_SELECT16_mem;
bool fe_SELECT16_bool;
function<char*()> fe_SELECT16;
char* fe_SELECT17_mem;
bool fe_SELECT17_bool;
function<char*()> fe_SELECT17;
char* fe_SELECT18_mem;
bool fe_SELECT18_bool;
function<char*()> fe_SELECT18;
char* fe_SELECT19_mem;
bool fe_SELECT19_bool;
function<char*()> fe_SELECT19;
char* fe_SELECT2_mem;
bool fe_SELECT2_bool;
function<char*()> fe_SELECT2;
char* fe_SELECT20_mem;
bool fe_SELECT20_bool;
function<char*()> fe_SELECT20;
char* fe_SELECT21_mem;
bool fe_SELECT21_bool;
function<char*()> fe_SELECT21;
char* fe_SELECT22_mem;
bool fe_SELECT22_bool;
function<char*()> fe_SELECT22;
char* fe_SELECT23_mem;
bool fe_SELECT23_bool;
function<char*()> fe_SELECT23;
char* fe_SELECT24_mem;
bool fe_SELECT24_bool;
function<char*()> fe_SELECT24;
char* fe_SELECT25_mem;
bool fe_SELECT25_bool;
function<char*()> fe_SELECT25;
char* fe_SELECT26_mem;
bool fe_SELECT26_bool;
function<char*()> fe_SELECT26;
char* fe_SELECT27_mem;
bool fe_SELECT27_bool;
function<char*()> fe_SELECT27;
char* fe_SELECT28_mem;
bool fe_SELECT28_bool;
function<char*()> fe_SELECT28;
char* fe_SELECT29_mem;
bool fe_SELECT29_bool;
function<char*()> fe_SELECT29;
char* fe_SELECT3_mem;
bool fe_SELECT3_bool;
function<char*()> fe_SELECT3;
char* fe_SELECT30_mem;
bool fe_SELECT30_bool;
function<char*()> fe_SELECT30;
char* fe_SELECT31_mem;
bool fe_SELECT31_bool;
function<char*()> fe_SELECT31;
char* fe_SELECT32_mem;
bool fe_SELECT32_bool;
function<char*()> fe_SELECT32;
char* fe_SELECT33_mem;
bool fe_SELECT33_bool;
function<char*()> fe_SELECT33;
char* fe_SELECT34_mem;
bool fe_SELECT34_bool;
function<char*()> fe_SELECT34;
char* fe_SELECT35_mem;
bool fe_SELECT35_bool;
function<char*()> fe_SELECT35;
char* fe_SELECT36_mem;
bool fe_SELECT36_bool;
function<char*()> fe_SELECT36;
char* fe_SELECT37_mem;
bool fe_SELECT37_bool;
function<char*()> fe_SELECT37;
char* fe_SELECT38_mem;
bool fe_SELECT38_bool;
function<char*()> fe_SELECT38;
char* fe_SELECT39_mem;
bool fe_SELECT39_bool;
function<char*()> fe_SELECT39;
char* fe_SELECT4_mem;
bool fe_SELECT4_bool;
function<char*()> fe_SELECT4;
char* fe_SELECT40_mem;
bool fe_SELECT40_bool;
function<char*()> fe_SELECT40;
char* fe_SELECT41_mem;
bool fe_SELECT41_bool;
function<char*()> fe_SELECT41;
char* fe_SELECT42_mem;
bool fe_SELECT42_bool;
function<char*()> fe_SELECT42;
char* fe_SELECT43_mem;
bool fe_SELECT43_bool;
function<char*()> fe_SELECT43;
char* fe_SELECT44_mem;
bool fe_SELECT44_bool;
function<char*()> fe_SELECT44;
char* fe_SELECT5_mem;
bool fe_SELECT5_bool;
function<char*()> fe_SELECT5;
char* fe_SELECT6_mem;
bool fe_SELECT6_bool;
function<char*()> fe_SELECT6;
char* fe_SELECT7_mem;
bool fe_SELECT7_bool;
function<char*()> fe_SELECT7;
char* fe_SELECT8_mem;
bool fe_SELECT8_bool;
function<char*()> fe_SELECT8;
char* fe_SELECT9_mem;
bool fe_SELECT9_bool;
function<char*()> fe_SELECT9;
char* fe_SLICE0_mem;
bool fe_SLICE0_bool;
function<char*()> fe_SLICE0;
char* fe_SLICE1_mem;
bool fe_SLICE1_bool;
function<char*()> fe_SLICE1;
char* fe_SLICE10_mem;
bool fe_SLICE10_bool;
function<char*()> fe_SLICE10;
char* fe_SLICE11_mem;
bool fe_SLICE11_bool;
function<char*()> fe_SLICE11;
char* fe_SLICE12_mem;
bool fe_SLICE12_bool;
function<char*()> fe_SLICE12;
char* fe_SLICE13_mem;
bool fe_SLICE13_bool;
function<char*()> fe_SLICE13;
char* fe_SLICE14_mem;
bool fe_SLICE14_bool;
function<char*()> fe_SLICE14;
char* fe_SLICE15_mem;
bool fe_SLICE15_bool;
function<char*()> fe_SLICE15;
char* fe_SLICE2_mem;
bool fe_SLICE2_bool;
function<char*()> fe_SLICE2;
char* fe_SLICE3_mem;
bool fe_SLICE3_bool;
function<char*()> fe_SLICE3;
char* fe_SLICE4_mem;
bool fe_SLICE4_bool;
function<char*()> fe_SLICE4;
char* fe_SLICE5_mem;
bool fe_SLICE5_bool;
function<char*()> fe_SLICE5;
char* fe_SLICE6_mem;
bool fe_SLICE6_bool;
function<char*()> fe_SLICE6;
char* fe_SLICE7_mem;
bool fe_SLICE7_bool;
function<char*()> fe_SLICE7;
char* fe_SLICE8_mem;
bool fe_SLICE8_bool;
function<char*()> fe_SLICE8;
char* fe_SLICE9_mem;
bool fe_SLICE9_bool;
function<char*()> fe_SLICE9;
char* fe_XOR0_mem;
bool fe_XOR0_bool;
function<char*()> fe_XOR0;
char* fe_XOR1_mem;
bool fe_XOR1_bool;
function<char*()> fe_XOR1;
char* fe_XOR10_mem;
bool fe_XOR10_bool;
function<char*()> fe_XOR10;
char* fe_XOR11_mem;
bool fe_XOR11_bool;
function<char*()> fe_XOR11;
char* fe_XOR12_mem;
bool fe_XOR12_bool;
function<char*()> fe_XOR12;
char* fe_XOR2_mem;
bool fe_XOR2_bool;
function<char*()> fe_XOR2;
char* fe_XOR3_mem;
bool fe_XOR3_bool;
function<char*()> fe_XOR3;
char* fe_XOR4_mem;
bool fe_XOR4_bool;
function<char*()> fe_XOR4;
char* fe_XOR5_mem;
bool fe_XOR5_bool;
function<char*()> fe_XOR5;
char* fe_XOR6_mem;
bool fe_XOR6_bool;
function<char*()> fe_XOR6;
char* fe_XOR7_mem;
bool fe_XOR7_bool;
function<char*()> fe_XOR7;
char* fe_XOR8_mem;
bool fe_XOR8_bool;
function<char*()> fe_XOR8;
char* fe_XOR9_mem;
bool fe_XOR9_bool;
function<char*()> fe_XOR9;


int main(int argc,char **argv)
{
    int step=-1;
    bool hexa=false;

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


    //creation des variables
	create_mem(&fe_0_mem,1,32);
	create_mem(&fe_AND0_mem,1,1);
	create_mem(&fe_AND1_mem,1,1);
	create_mem(&fe_AND10_mem,1,1);
	create_mem(&fe_AND11_mem,1,1);
	create_mem(&fe_AND12_mem,1,1);
	create_mem(&fe_AND13_mem,1,1);
	create_mem(&fe_AND14_mem,1,1);
	create_mem(&fe_AND15_mem,1,1);
	create_mem(&fe_AND16_mem,1,1);
	create_mem(&fe_AND17_mem,1,1);
	create_mem(&fe_AND18_mem,1,1);
	create_mem(&fe_AND19_mem,1,1);
	create_mem(&fe_AND2_mem,1,1);
	create_mem(&fe_AND20_mem,1,1);
	create_mem(&fe_AND21_mem,1,1);
	create_mem(&fe_AND22_mem,1,1);
	create_mem(&fe_AND23_mem,1,1);
	create_mem(&fe_AND24_mem,1,1);
	create_mem(&fe_AND25_mem,1,1);
	create_mem(&fe_AND26_mem,1,1);
	create_mem(&fe_AND27_mem,1,1);
	create_mem(&fe_AND28_mem,1,1);
	create_mem(&fe_AND29_mem,1,1);
	create_mem(&fe_AND3_mem,1,1);
	create_mem(&fe_AND30_mem,1,1);
	create_mem(&fe_AND31_mem,1,1);
	create_mem(&fe_AND32_mem,1,1);
	create_mem(&fe_AND33_mem,1,1);
	create_mem(&fe_AND34_mem,1,1);
	create_mem(&fe_AND35_mem,1,1);
	create_mem(&fe_AND36_mem,1,1);
	create_mem(&fe_AND37_mem,1,1);
	create_mem(&fe_AND38_mem,1,1);
	create_mem(&fe_AND39_mem,1,1);
	create_mem(&fe_AND4_mem,1,1);
	create_mem(&fe_AND40_mem,1,1);
	create_mem(&fe_AND41_mem,1,1);
	create_mem(&fe_AND42_mem,1,1);
	create_mem(&fe_AND43_mem,1,1);
	create_mem(&fe_AND44_mem,1,1);
	create_mem(&fe_AND45_mem,1,1);
	create_mem(&fe_AND46_mem,1,1);
	create_mem(&fe_AND47_mem,1,1);
	create_mem(&fe_AND48_mem,1,1);
	create_mem(&fe_AND49_mem,1,1);
	create_mem(&fe_AND5_mem,1,1);
	create_mem(&fe_AND50_mem,1,1);
	create_mem(&fe_AND51_mem,1,1);
	create_mem(&fe_AND52_mem,1,1);
	create_mem(&fe_AND53_mem,1,1);
	create_mem(&fe_AND54_mem,1,1);
	create_mem(&fe_AND55_mem,1,1);
	create_mem(&fe_AND56_mem,1,1);
	create_mem(&fe_AND57_mem,1,1);
	create_mem(&fe_AND58_mem,1,1);
	create_mem(&fe_AND59_mem,1,1);
	create_mem(&fe_AND6_mem,1,1);
	create_mem(&fe_AND60_mem,1,1);
	create_mem(&fe_AND61_mem,1,1);
	create_mem(&fe_AND62_mem,1,1);
	create_mem(&fe_AND63_mem,1,1);
	create_mem(&fe_AND64_mem,1,1);
	create_mem(&fe_AND65_mem,1,1);
	create_mem(&fe_AND66_mem,1,1);
	create_mem(&fe_AND67_mem,1,1);
	create_mem(&fe_AND68_mem,1,1);
	create_mem(&fe_AND69_mem,1,1);
	create_mem(&fe_AND7_mem,1,1);
	create_mem(&fe_AND70_mem,1,1);
	create_mem(&fe_AND71_mem,1,1);
	create_mem(&fe_AND72_mem,1,1);
	create_mem(&fe_AND73_mem,1,1);
	create_mem(&fe_AND74_mem,1,1);
	create_mem(&fe_AND75_mem,1,1);
	create_mem(&fe_AND76_mem,1,1);
	create_mem(&fe_AND77_mem,1,1);
	create_mem(&fe_AND8_mem,1,1);
	create_mem(&fe_AND9_mem,1,1);
	create_mem(&fe_CONCAT0_mem,1,32);
	create_mem(&fe_CONCAT1_mem,1,2);
	create_mem(&fe_CONCAT10_mem,1,2);
	create_mem(&fe_CONCAT11_mem,1,3);
	create_mem(&fe_CONCAT12_mem,1,6);
	create_mem(&fe_CONCAT13_mem,1,2);
	create_mem(&fe_CONCAT14_mem,1,3);
	create_mem(&fe_CONCAT15_mem,1,2);
	create_mem(&fe_CONCAT16_mem,1,2);
	create_mem(&fe_CONCAT17_mem,1,4);
	create_mem(&fe_CONCAT18_mem,1,7);
	create_mem(&fe_CONCAT19_mem,1,13);
	create_mem(&fe_CONCAT2_mem,1,2);
	create_mem(&fe_CONCAT3_mem,1,4);
	create_mem(&fe_CONCAT4_mem,1,2);
	create_mem(&fe_CONCAT5_mem,1,0);
	create_mem(&fe_CONCAT6_mem,1,2);
	create_mem(&fe_CONCAT7_mem,1,6);
	create_mem(&fe_CONCAT8_mem,1,2);
	create_mem(&fe_CONCAT9_mem,1,3);
	create_mem(&fe_MUX1_mem,1,32);
	create_mem(&fe_MUX10_mem,1,3);
	create_mem(&fe_MUX11_mem,1,3);
	create_mem(&fe_MUX12_mem,1,3);
	create_mem(&fe_MUX13_mem,1,3);
	create_mem(&fe_MUX14_mem,1,3);
	create_mem(&fe_MUX15_mem,1,3);
	create_mem(&fe_MUX16_mem,1,3);
	create_mem(&fe_MUX17_mem,1,3);
	create_mem(&fe_MUX18_mem,1,3);
	create_mem(&fe_MUX19_mem,1,3);
	create_mem(&fe_MUX2_mem,1,32);
	create_mem(&fe_MUX20_mem,1,3);
	create_mem(&fe_MUX21_mem,1,3);
	create_mem(&fe_MUX22_mem,1,3);
	create_mem(&fe_MUX23_mem,1,3);
	create_mem(&fe_MUX24_mem,1,3);
	create_mem(&fe_MUX25_mem,1,3);
	create_mem(&fe_MUX26_mem,1,3);
	create_mem(&fe_MUX27_mem,1,3);
	create_mem(&fe_MUX28_mem,1,3);
	create_mem(&fe_MUX29_mem,1,3);
	create_mem(&fe_MUX3_mem,1,3);
	create_mem(&fe_MUX30_mem,1,3);
	create_mem(&fe_MUX31_mem,1,3);
	create_mem(&fe_MUX32_mem,1,3);
	create_mem(&fe_MUX33_mem,1,3);
	create_mem(&fe_MUX34_mem,1,3);
	create_mem(&fe_MUX35_mem,1,3);
	create_mem(&fe_MUX36_mem,1,3);
	create_mem(&fe_MUX37_mem,1,3);
	create_mem(&fe_MUX38_mem,1,3);
	create_mem(&fe_MUX39_mem,1,3);
	create_mem(&fe_MUX4_mem,1,3);
	create_mem(&fe_MUX40_mem,1,3);
	create_mem(&fe_MUX41_mem,1,3);
	create_mem(&fe_MUX42_mem,1,3);
	create_mem(&fe_MUX43_mem,1,3);
	create_mem(&fe_MUX44_mem,1,3);
	create_mem(&fe_MUX45_mem,1,3);
	create_mem(&fe_MUX46_mem,1,3);
	create_mem(&fe_MUX47_mem,1,3);
	create_mem(&fe_MUX48_mem,1,3);
	create_mem(&fe_MUX49_mem,1,3);
	create_mem(&fe_MUX5_mem,1,3);
	create_mem(&fe_MUX50_mem,1,3);
	create_mem(&fe_MUX51_mem,1,1);
	create_mem(&fe_MUX6_mem,1,3);
	create_mem(&fe_MUX7_mem,1,3);
	create_mem(&fe_MUX8_mem,1,3);
	create_mem(&fe_MUX9_mem,1,3);
	create_mem(&fe_NOT0_mem,1,1);
	create_mem(&fe_NOT1_mem,1,1);
	create_mem(&fe_NOT10_mem,1,1);
	create_mem(&fe_NOT11_mem,1,1);
	create_mem(&fe_NOT12_mem,1,1);
	create_mem(&fe_NOT13_mem,1,1);
	create_mem(&fe_NOT14_mem,1,1);
	create_mem(&fe_NOT15_mem,1,1);
	create_mem(&fe_NOT16_mem,1,1);
	create_mem(&fe_NOT17_mem,1,1);
	create_mem(&fe_NOT18_mem,1,1);
	create_mem(&fe_NOT19_mem,1,1);
	create_mem(&fe_NOT2_mem,1,1);
	create_mem(&fe_NOT20_mem,1,1);
	create_mem(&fe_NOT21_mem,1,1);
	create_mem(&fe_NOT22_mem,1,1);
	create_mem(&fe_NOT3_mem,1,1);
	create_mem(&fe_NOT4_mem,1,1);
	create_mem(&fe_NOT5_mem,1,1);
	create_mem(&fe_NOT6_mem,1,1);
	create_mem(&fe_NOT7_mem,1,1);
	create_mem(&fe_NOT8_mem,1,1);
	create_mem(&fe_NOT9_mem,1,1);
	create_mem(&fe_OR0_mem,1,1);
	create_mem(&fe_OR1_mem,1,1);
	create_mem(&fe_OR10_mem,1,1);
	create_mem(&fe_OR11_mem,1,1);
	create_mem(&fe_OR2_mem,1,1);
	create_mem(&fe_OR3_mem,1,1);
	create_mem(&fe_OR4_mem,1,1);
	create_mem(&fe_OR5_mem,1,1);
	create_mem(&fe_OR6_mem,1,1);
	create_mem(&fe_OR7_mem,1,1);
	create_mem(&fe_OR8_mem,1,1);
	create_mem(&fe_OR9_mem,1,1);
	create_mem(&fe_RAM0_mem,1,32);
	create_mem(&fe_REG0_mem,1,3);
	create_mem(&fe_REG1_mem,1,3);
	create_mem(&fe_REG10_mem,1,3);
	create_mem(&fe_REG11_mem,1,3);
	create_mem(&fe_REG12_mem,1,3);
	create_mem(&fe_REG13_mem,1,3);
	create_mem(&fe_REG14_mem,1,3);
	create_mem(&fe_REG15_mem,1,3);
	create_mem(&fe_REG16_mem,1,2);
	create_mem(&fe_REG17_mem,1,13);
	create_mem(&fe_REG2_mem,1,3);
	create_mem(&fe_REG3_mem,1,3);
	create_mem(&fe_REG4_mem,1,3);
	create_mem(&fe_REG5_mem,1,3);
	create_mem(&fe_REG6_mem,1,3);
	create_mem(&fe_REG7_mem,1,3);
	create_mem(&fe_REG8_mem,1,3);
	create_mem(&fe_REG9_mem,1,3);
	create_mem(&fe_ROM0_mem,1,32);
	create_mem(&fe_SELECT0_mem,1,1);
	create_mem(&fe_SELECT1_mem,1,1);
	create_mem(&fe_SELECT10_mem,1,1);
	create_mem(&fe_SELECT11_mem,1,1);
	create_mem(&fe_SELECT12_mem,1,1);
	create_mem(&fe_SELECT13_mem,1,1);
	create_mem(&fe_SELECT14_mem,1,1);
	create_mem(&fe_SELECT15_mem,1,1);
	create_mem(&fe_SELECT16_mem,1,1);
	create_mem(&fe_SELECT17_mem,1,1);
	create_mem(&fe_SELECT18_mem,1,1);
	create_mem(&fe_SELECT19_mem,1,1);
	create_mem(&fe_SELECT2_mem,1,1);
	create_mem(&fe_SELECT20_mem,1,1);
	create_mem(&fe_SELECT21_mem,1,1);
	create_mem(&fe_SELECT22_mem,1,1);
	create_mem(&fe_SELECT23_mem,1,1);
	create_mem(&fe_SELECT24_mem,1,1);
	create_mem(&fe_SELECT25_mem,1,1);
	create_mem(&fe_SELECT26_mem,1,1);
	create_mem(&fe_SELECT27_mem,1,1);
	create_mem(&fe_SELECT28_mem,1,1);
	create_mem(&fe_SELECT29_mem,1,1);
	create_mem(&fe_SELECT3_mem,1,1);
	create_mem(&fe_SELECT30_mem,1,0);
	create_mem(&fe_SELECT31_mem,1,1);
	create_mem(&fe_SELECT32_mem,1,1);
	create_mem(&fe_SELECT33_mem,1,1);
	create_mem(&fe_SELECT34_mem,1,1);
	create_mem(&fe_SELECT35_mem,1,1);
	create_mem(&fe_SELECT36_mem,1,1);
	create_mem(&fe_SELECT37_mem,1,1);
	create_mem(&fe_SELECT38_mem,1,1);
	create_mem(&fe_SELECT39_mem,1,1);
	create_mem(&fe_SELECT4_mem,1,1);
	create_mem(&fe_SELECT40_mem,1,1);
	create_mem(&fe_SELECT41_mem,1,1);
	create_mem(&fe_SELECT42_mem,1,1);
	create_mem(&fe_SELECT43_mem,1,1);
	create_mem(&fe_SELECT44_mem,1,1);
	create_mem(&fe_SELECT5_mem,1,1);
	create_mem(&fe_SELECT6_mem,1,1);
	create_mem(&fe_SELECT7_mem,1,1);
	create_mem(&fe_SELECT8_mem,1,1);
	create_mem(&fe_SELECT9_mem,1,1);
	create_mem(&fe_SLICE0_mem,1,2);
	create_mem(&fe_SLICE1_mem,1,1);
	create_mem(&fe_SLICE10_mem,1,4);
	create_mem(&fe_SLICE11_mem,1,4);
	create_mem(&fe_SLICE12_mem,1,13);
	create_mem(&fe_SLICE13_mem,1,13);
	create_mem(&fe_SLICE14_mem,1,13);
	create_mem(&fe_SLICE15_mem,1,13);
	create_mem(&fe_SLICE2_mem,1,1);
	create_mem(&fe_SLICE3_mem,1,4);
	create_mem(&fe_SLICE4_mem,1,2);
	create_mem(&fe_SLICE5_mem,1,1);
	create_mem(&fe_SLICE6_mem,1,1);
	create_mem(&fe_SLICE7_mem,1,2);
	create_mem(&fe_SLICE8_mem,1,1);
	create_mem(&fe_SLICE9_mem,1,1);
	create_mem(&fe_XOR0_mem,1,1);
	create_mem(&fe_XOR1_mem,1,1);
	create_mem(&fe_XOR10_mem,1,1);
	create_mem(&fe_XOR11_mem,1,1);
	create_mem(&fe_XOR12_mem,1,1);
	create_mem(&fe_XOR2_mem,1,1);
	create_mem(&fe_XOR3_mem,1,1);
	create_mem(&fe_XOR4_mem,1,1);
	create_mem(&fe_XOR5_mem,1,1);
	create_mem(&fe_XOR6_mem,1,1);
	create_mem(&fe_XOR7_mem,1,1);
	create_mem(&fe_XOR8_mem,1,1);
	create_mem(&fe_XOR9_mem,1,1);


    //creation des registres


    //equations
	fe_ROM0=([](){
		if(!fe_ROM0_bool) copy(fe_ROM0_rom,fe_ROM0_mem,to_int(fe_REG17(),0,13),0,32);
		fe_ROM0_bool=true;
		return fe_ROM0_mem;
	});
	fe_SLICE3=([](){
		if(!fe_SLICE3_bool) op_slice(fe_SLICE3_mem,0,3,fe_ROM0());
		fe_SLICE3_bool=true;
		return fe_SLICE3_mem;
	});
	fe_SLICE4=([](){
		if(!fe_SLICE4_bool) op_slice(fe_SLICE4_mem,0,1,fe_SLICE3());
		fe_SLICE4_bool=true;
		return fe_SLICE4_mem;
	});
	fe_SLICE5=([](){
		if(!fe_SLICE5_bool) op_slice(fe_SLICE5_mem,0,0,fe_SLICE4());
		fe_SLICE5_bool=true;
		return fe_SLICE5_mem;
	});
	fe_SLICE6=([](){
		if(!fe_SLICE6_bool) op_slice(fe_SLICE6_mem,1,1,fe_SLICE4());
		fe_SLICE6_bool=true;
		return fe_SLICE6_mem;
	});
	fe_AND7=([](){
		if(!fe_AND7_bool) op_and(fe_AND7_mem,fe_SLICE5(),fe_SLICE6(),1);
		fe_AND7_bool=true;
		return fe_AND7_mem;
	});
	fe_SLICE7=([](){
		if(!fe_SLICE7_bool) op_slice(fe_SLICE7_mem,2,3,fe_SLICE3());
		fe_SLICE7_bool=true;
		return fe_SLICE7_mem;
	});
	fe_SLICE8=([](){
		if(!fe_SLICE8_bool) op_slice(fe_SLICE8_mem,0,0,fe_SLICE7());
		fe_SLICE8_bool=true;
		return fe_SLICE8_mem;
	});
	fe_SLICE9=([](){
		if(!fe_SLICE9_bool) op_slice(fe_SLICE9_mem,1,1,fe_SLICE7());
		fe_SLICE9_bool=true;
		return fe_SLICE9_mem;
	});
	fe_AND11=([](){
		if(!fe_AND11_bool) op_and(fe_AND11_mem,fe_SLICE8(),fe_SLICE9(),1);
		fe_AND11_bool=true;
		return fe_AND11_mem;
	});
	fe_AND27=([](){
		if(!fe_AND27_bool) op_and(fe_AND27_mem,fe_AND7(),fe_AND11(),1);
		fe_AND27_bool=true;
		return fe_AND27_mem;
	});
	fe_NOT5=([](){
		if(!fe_NOT5_bool) op_not(fe_NOT5_mem,fe_SLICE9(),1);
		fe_NOT5_bool=true;
		return fe_NOT5_mem;
	});
	fe_AND10=([](){
		if(!fe_AND10_bool) op_and(fe_AND10_mem,fe_SLICE8(),fe_NOT5(),1);
		fe_AND10_bool=true;
		return fe_AND10_mem;
	});
	fe_AND26=([](){
		if(!fe_AND26_bool) op_and(fe_AND26_mem,fe_AND7(),fe_AND10(),1);
		fe_AND26_bool=true;
		return fe_AND26_mem;
	});
	fe_NOT4=([](){
		if(!fe_NOT4_bool) op_not(fe_NOT4_mem,fe_SLICE8(),1);
		fe_NOT4_bool=true;
		return fe_NOT4_mem;
	});
	fe_AND9=([](){
		if(!fe_AND9_bool) op_and(fe_AND9_mem,fe_NOT4(),fe_SLICE9(),1);
		fe_AND9_bool=true;
		return fe_AND9_mem;
	});
	fe_AND25=([](){
		if(!fe_AND25_bool) op_and(fe_AND25_mem,fe_AND7(),fe_AND9(),1);
		fe_AND25_bool=true;
		return fe_AND25_mem;
	});
	fe_AND8=([](){
		if(!fe_AND8_bool) op_and(fe_AND8_mem,fe_NOT4(),fe_NOT5(),1);
		fe_AND8_bool=true;
		return fe_AND8_mem;
	});
	fe_AND24=([](){
		if(!fe_AND24_bool) op_and(fe_AND24_mem,fe_AND7(),fe_AND8(),1);
		fe_AND24_bool=true;
		return fe_AND24_mem;
	});
	fe_NOT3=([](){
		if(!fe_NOT3_bool) op_not(fe_NOT3_mem,fe_SLICE6(),1);
		fe_NOT3_bool=true;
		return fe_NOT3_mem;
	});
	fe_AND6=([](){
		if(!fe_AND6_bool) op_and(fe_AND6_mem,fe_SLICE5(),fe_NOT3(),1);
		fe_AND6_bool=true;
		return fe_AND6_mem;
	});
	fe_AND23=([](){
		if(!fe_AND23_bool) op_and(fe_AND23_mem,fe_AND6(),fe_AND11(),1);
		fe_AND23_bool=true;
		return fe_AND23_mem;
	});
	fe_AND22=([](){
		if(!fe_AND22_bool) op_and(fe_AND22_mem,fe_AND6(),fe_AND10(),1);
		fe_AND22_bool=true;
		return fe_AND22_mem;
	});
	fe_AND21=([](){
		if(!fe_AND21_bool) op_and(fe_AND21_mem,fe_AND6(),fe_AND9(),1);
		fe_AND21_bool=true;
		return fe_AND21_mem;
	});
	fe_AND20=([](){
		if(!fe_AND20_bool) op_and(fe_AND20_mem,fe_AND6(),fe_AND8(),1);
		fe_AND20_bool=true;
		return fe_AND20_mem;
	});
	fe_NOT2=([](){
		if(!fe_NOT2_bool) op_not(fe_NOT2_mem,fe_SLICE5(),1);
		fe_NOT2_bool=true;
		return fe_NOT2_mem;
	});
	fe_AND5=([](){
		if(!fe_AND5_bool) op_and(fe_AND5_mem,fe_NOT2(),fe_SLICE6(),1);
		fe_AND5_bool=true;
		return fe_AND5_mem;
	});
	fe_AND19=([](){
		if(!fe_AND19_bool) op_and(fe_AND19_mem,fe_AND5(),fe_AND11(),1);
		fe_AND19_bool=true;
		return fe_AND19_mem;
	});
	fe_AND18=([](){
		if(!fe_AND18_bool) op_and(fe_AND18_mem,fe_AND5(),fe_AND10(),1);
		fe_AND18_bool=true;
		return fe_AND18_mem;
	});
	fe_AND17=([](){
		if(!fe_AND17_bool) op_and(fe_AND17_mem,fe_AND5(),fe_AND9(),1);
		fe_AND17_bool=true;
		return fe_AND17_mem;
	});
	fe_AND16=([](){
		if(!fe_AND16_bool) op_and(fe_AND16_mem,fe_AND5(),fe_AND8(),1);
		fe_AND16_bool=true;
		return fe_AND16_mem;
	});
	fe_AND4=([](){
		if(!fe_AND4_bool) op_and(fe_AND4_mem,fe_NOT2(),fe_NOT3(),1);
		fe_AND4_bool=true;
		return fe_AND4_mem;
	});
	fe_AND15=([](){
		if(!fe_AND15_bool) op_and(fe_AND15_mem,fe_AND4(),fe_AND11(),1);
		fe_AND15_bool=true;
		return fe_AND15_mem;
	});
	fe_AND14=([](){
		if(!fe_AND14_bool) op_and(fe_AND14_mem,fe_AND4(),fe_AND10(),1);
		fe_AND14_bool=true;
		return fe_AND14_mem;
	});
	fe_AND13=([](){
		if(!fe_AND13_bool) op_and(fe_AND13_mem,fe_AND4(),fe_AND9(),1);
		fe_AND13_bool=true;
		return fe_AND13_mem;
	});
	fe_AND12=([](){
		if(!fe_AND12_bool) op_and(fe_AND12_mem,fe_AND4(),fe_AND8(),1);
		fe_AND12_bool=true;
		return fe_AND12_mem;
	});
	fe_SLICE0=([](){
		if(!fe_SLICE0_bool) op_slice(fe_SLICE0_mem,4,5,fe_ROM0());
		fe_SLICE0_bool=true;
		return fe_SLICE0_mem;
	});
	fe_SLICE1=([](){
		if(!fe_SLICE1_bool) op_slice(fe_SLICE1_mem,0,0,fe_SLICE0());
		fe_SLICE1_bool=true;
		return fe_SLICE1_mem;
	});
	fe_SLICE2=([](){
		if(!fe_SLICE2_bool) op_slice(fe_SLICE2_mem,1,1,fe_SLICE0());
		fe_SLICE2_bool=true;
		return fe_SLICE2_mem;
	});
	fe_AND3=([](){
		if(!fe_AND3_bool) op_and(fe_AND3_mem,fe_SLICE1(),fe_SLICE2(),1);
		fe_AND3_bool=true;
		return fe_AND3_mem;
	});
	fe_NOT1=([](){
		if(!fe_NOT1_bool) op_not(fe_NOT1_mem,fe_SLICE2(),1);
		fe_NOT1_bool=true;
		return fe_NOT1_mem;
	});
	fe_AND2=([](){
		if(!fe_AND2_bool) op_and(fe_AND2_mem,fe_SLICE1(),fe_NOT1(),1);
		fe_AND2_bool=true;
		return fe_AND2_mem;
	});
	fe_NOT0=([](){
		if(!fe_NOT0_bool) op_not(fe_NOT0_mem,fe_SLICE1(),1);
		fe_NOT0_bool=true;
		return fe_NOT0_mem;
	});
	fe_AND1=([](){
		if(!fe_AND1_bool) op_and(fe_AND1_mem,fe_NOT0(),fe_SLICE2(),1);
		fe_AND1_bool=true;
		return fe_AND1_mem;
	});
	fe_AND0=([](){
		if(!fe_AND0_bool) op_and(fe_AND0_mem,fe_NOT0(),fe_NOT1(),1);
		fe_AND0_bool=true;
		return fe_AND0_mem;
	});


    while(step!=0)
    {
        step--;
        //inputs
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


        //outputs


        //actualisation des registres

    }
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

void print(char *mem,int addr,int word_size)
{
    for(int i=0;i<word_size;i++)
    {
        cout<<get_bit(mem,addr*word_size+i);
    }
    cout<<endl;
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