Requests:
  SET
  REGISTER
  UNREGISTER

Examples:
  REGISTER Log.txt HTTP/2.0   //register new log
  SET Log.txt?UpdatePeriod=4 HTTP/2.0   //setting the period of updating
  UNREGISTER Log.txt HTTP/2.0   //unregister from log storage
