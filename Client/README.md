Requests:
  PUT
  POST
  DELETE

Examples:
  POST HTTP/1.1 /Log/6?UpdatePeriod=25&Path=fileName.txt   //register fileName.txt with updatePer = 25 and id = 6
  PUT HTTP/1.1 /Log/6   //flush log from file with id = 6
  DELETE HTTP/1.1 /Log/6   //delete log with id = 6
