curl --form name=myfileparam --form file=@data/test/in/basic_bold_S.jpg \
  -Fjson='{"parameter": {"name": "myfileparam", "file": "file"}}' \
  -Fsubmit=Build \
  http://localhost:8080/build
