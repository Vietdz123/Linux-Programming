cmd_/home/wibu/working_space/git/Linux_Programming/Bai12-CharacterDivice-IoctDiviceDriver/02_create-device-file/Module.symvers := sed 's/\.ko$$/\.o/' /home/wibu/working_space/git/Linux_Programming/Bai12-CharacterDivice-IoctDiviceDriver/02_create-device-file/modules.order | scripts/mod/modpost -m -a  -o /home/wibu/working_space/git/Linux_Programming/Bai12-CharacterDivice-IoctDiviceDriver/02_create-device-file/Module.symvers -e -i Module.symvers   -T -
