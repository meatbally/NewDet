# file is located at TOF

# 156.55 MeV # 155.54 # 154.53 # 157.56
cd ..
cd TOF_SD2-build
make
./exampleB4c -m run1.mac

# 155.775 MeV # 154.77 # 153.765 # 156.78
cd ..
cd TOF_SD2
cd src
sed -i '.bak' 's/157.56/156.78/g' B4PrimaryGeneratorAction.cc
sed -i '.bak' 's/p1/p2/g' B4RunAction.cc
cd ..
cd ..
cd TOF_SD2-build
make
./exampleB4c -m run1.mac

# 155 MeV # 154 # 153 # 156
cd ..
cd TOF_SD2
cd src
sed -i '.bak' 's/156.78/156.0/g' B4PrimaryGeneratorAction.cc
sed -i '.bak' 's/p2/p3/g' B4RunAction.cc
cd ..
cd ..
cd TOF_SD2-build
make
./exampleB4c -m run1.mac

# 154.225 MeV # 153.23 # 152.235 # 155.22
cd ..
cd TOF_SD2
cd src
sed -i '.bak' 's/156.0/155.22/g' B4PrimaryGeneratorAction.cc
sed -i '.bak' 's/p3/p4/g' B4RunAction.cc
cd ..
cd ..
cd TOF_SD2-build
make
./exampleB4c -m run1.mac

# 153.45 MeV # 152.46 # 151.47 # 154.44
cd ..
cd TOF_SD2
cd src
sed -i '.bak' 's/155.22/154.44/g' B4PrimaryGeneratorAction.cc
sed -i '.bak' 's/p4/p5/g' B4RunAction.cc
cd ..
cd ..
cd TOF_SD2-build
make
./exampleB4c -m run1.mac

# 152.675 MeV # 151.69 # 150.705 # 153.66
cd ..
cd TOF_SD2
cd src
sed -i '.bak' 's/154.44/153.66/g' B4PrimaryGeneratorAction.cc
sed -i '.bak' 's/p5/p6/g' B4RunAction.cc
cd ..
cd ..
cd TOF_SD2-build
make
./exampleB4c -m run1.mac

# reset
cd ..
cd TOF_SD2
cd src
sed -i '.bak' 's/153.66/157.56/g' B4PrimaryGeneratorAction.cc
sed -i '.bak' 's/p6/p1/g' B4RunAction.cc