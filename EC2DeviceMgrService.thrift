include "EC2Common.thrift"

service EC2DeviceMgrService {
    void updateHardwareInfo(EC2Common.HardwareInfo hardwareInfo),

    void addAlarm(string moduleName, EC2Common.AlarmInfo alarmInfo),
    void removeAlarm(string moduleName, EC2Common.AlarmInfo alarmInfo),
    void clearAlarm(string moduleName),

    string getDeviceID()
}