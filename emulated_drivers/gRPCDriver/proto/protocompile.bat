SET import="C:\protobuf\include"
SET out="out"
mkdir %out%
protoc --proto_path=. --proto_path="%import%" --cpp_out=%out% --csharp_out=%out% commands.proto
protoc --proto_path=. --proto_path="%import%" --cpp_out=%out% --csharp_out=%out% pose.proto
pause