/****Chuyên ngành****/
chuyenNganh(kyThuatPhanMem).
chuyenNganh(heThongThongTin).
chuyenNganh(congNgheTriThuc).
chuyenNganh(khoaHocMayTinh).
chuyenNganh(thiGiacMayTinh).
chuyenNganh(mangMayTinhVaVienThong).


/****Bộ môn****/
boMon(congNghePhanMem).
boMon(heThongThongTin_bm).
boMon(congNgheTriThuc_bm).
boMon(khoaHocMayTinh_bm).
boMon(thiGiacMayTinh_bm).
boMon(mangMayTinhVaVienThong_bm).


/****Giáo viên thuộc bộ môn****/
giaoVienThuocBoMon(leVanB,congNghePhanMem_bm).
giaoVienThuocBoMon(dangVanB,congNghePhanMem_bm).
giaoVienThuocBoMon(tranVanA,heThongThongTin_bm).
giaoVienThuocBoMon(tranVanB,heThongThongTin_bm).
giaoVienThuocBoMon(dangVanC,congNgheTriThuc_bm).
giaoVienThuocBoMon(tranVanC,khoaHocMayTinh_bm).
giaoVienThuocBoMon(leVanA,khoaHocMayTinh_bm).
giaoVienThuocBoMon(nguyenThiA,khoaHocMayTinh_bm).
giaoVienThuocBoMon(leVanC,thiGiacMayTinh_bm).
giaoVienThuocBoMon(nguyenThiB,thiGiacMayTinh_bm).
giaoVienThuocBoMon(dangVanA,mangMayTinhVaVienThong_bm).



/****Trình độ giáo viên****/
giaoSu(nguyenThiA).
phoGiaoSu(dangVanB).
phoGiaoSu(leVanC).
tienSi(tranVanA).
tienSi(tranVanB).
thacSi(tranVanC).
thacSi(leVanB).
thacSi(dangVanA).
thacSi(nguyenThiB).

/****Các lớp****/
lop(ctt1).
lop(ctt2).
lop(ctt3).
lop(ctt4).
lop(ctt5).

/****GV chủ nhiệm****/
chuNhiem(dangVanB,ctt1).
chuNhiem(tranVanC,ctt2).
chuNhiem(dangVanA,ctt3)
chuNhiem(nguyenThiB,ctt4).
chuNhiem(tranVanB,ctt5).


/****Vài ví dụ về sinh viên các lớp****/
sinhVienCuaLop(lyVanA,ctt1).
sinhVienCuaLop(traVanA,ctt1).
sinhVienCuaLop(lyVanB,ctt5).
sinhVienCuaLop(lyThiC,ctt5).
sinhVienCuaLop(traVanB,ctt2).
sinhVienCuaLop(traThiC,ctt2).
sinhVienCuaLop(nguyenVanAA,ctt4).
sinhVienCuaLop(nguyenVanBB,ctt3).


/****Bộ môn của ngành****/
boMonCuaNganh(congNghePhanMem_bm,kyThuatPhanMem).
boMonCuaNganh(heThongThongTin_bm,heThongThongTin).
boMonCuaNganh(thiGiacMayTinh_bm,thiGiacMayTinh).
boMonCuaNganh(khoaHocMayTinh_bm,khoaHocMayTinh).
boMonCuaNganh(congNgheTriThuc_bm,congNgheTriThuc).
boMonCuaNganh(mangMayTinhVaVienThong_bm,mangMayTinhVaVienThong).


/**** Trưởng khoa và phó khoa****/
truongKhoa(nguyenThiA).
phoKhoa(dangVanB).
phoKhoa(leVanC).


/****Các quan hệ****/
sinhVienTheoChuyenNganh(SV,CN):-sinhVienCuaLop(SV,CL),chuNhiem(GV,CL),giaoVienThuocBoMon(GV,BM), boMonCuaNganh(BM,CN).
giaoVienThuocChuyenNganh(GV, CN):-giaoVienThuocBoMon(GV,BM), boMonCuaNganh(BM,CN).
chuNhiemCuaSinhVien(GV,SV):-chuNhiem(GV,CL), sinhVienCuaLop(SV,CL).
boMonTheoHoc(SV,BM):-sinhVienCuaLop(SV,CL),chuNhiem(GV,CL),giaoVienThuocBoMon(GV,BM).
truongBoMon(GV, BM):-chuNhiem(GV,_),giaoVienThuocBoMon(GV,BM),tienSi(GV).
coTheLamPhoKhoa(GV):-truongBoMon(GV,_),phoGiaoSu(GV).
coTheLamTruongKhoa(GV):-truongBoMon(GV,_),giaoSu(GV).
tienSiCuaNganh(GV,CN):-giaoVienThuocChuyenNganh(GV,CN),tienSi(GV).
thacSiCuaNganh(GV,CN):-giaoVienThuocChuyenNganh(GV,CN),thacSi(GV).
phoGiaoSuCuaNganh(GV,CN):-giaoVienThuocChuyenNganh(GV,CN), phoGiaoSu(GV).
giaoSuCuaNganh(GV,CN):-giaoVienThuocChuyenNganh(GV,CN), giaoSu(GV).
lopTheoChuyenNganh(CL,CN):-chuNhiem(GV,CL), giaoVienThuocBoMon(GV,BM), boMonCuaNganh(BM,CN).
lopTheoBoMon(CL,BM):-chuNhiem(GV,CL), giaoVienThuocBoMon(GV,BM).

