make clean;
make;
rm -rf ~/package/CodeGenerator ~/package/CodeGenerator.tar.gz;
mkdir ~/package/CodeGenerator;
cp generator.app ~/package/CodeGenerator/generate;
cp -r ./etc ~/package/CodeGenerator/etc;
cp -r ./project ~/package/CodeGenerator/project;
cd ~/package;
tar -zcvf CodeGenerator.tar.gz *;
rm -rf CodeGenerator;