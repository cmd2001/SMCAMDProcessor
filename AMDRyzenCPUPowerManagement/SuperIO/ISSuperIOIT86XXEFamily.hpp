//
//  ISSuperIOIT86XXEFamily.hpp
//  AMDRyzenCPUPowerManagement
//
//  Created by Maurice on 25.05.20.
//

#ifndef ISSuperIOIT86XXEFamily_hpp
#define ISSuperIOIT86XXEFamily_hpp

#include <IOKit/IOLib.h>

#include <architecture/i386/pio.h>

#include "ISLPCPort.h"
#include "ISSuperIOSMCFamily.hpp"

#define CHIP_IT8688E 0x8688
#define CHIP_IT8686E 0x8686
#define CHIP_IT8665E 0x8665
#define CHIP_ITE8638 0x8638

#define IT86XXE_MAX_NUMFAN 5

#define CHIP_ENVIRONMENT_CONTROLLER_LDN 0x04
#define CHIP_GPIO_LDN 0x07

#define CHIP_ADDR_REG_OFFSET 0x05
#define CHIP_DAT_REG_OFFSET 0x06

class ISSuperIOIT86XXEFamily : public ISSuperIOSMCFamily
{

  public:
    static constexpr const char* kFAN_READABLE_STRS[] = {
        "CPU Fan",
        "System 1 Fan",
        "System 2 Fan",
        "PCH Fan",
        "CPU OPT Fan",
    };

    static ISSuperIOIT86XXEFamily* getDevice(uint16_t* chipIntel);

    ISSuperIOIT86XXEFamily(int psel, uint16_t addr, uint16_t chipIntel);

    int fanRPMs[IT86XXE_MAX_NUMFAN];
    uint8_t fanControlMode[IT86XXE_MAX_NUMFAN];

    int activeFansOnSystem = 0;

    int getNumberOfFans() override;
    const char* getReadableStringForFan(int fan) override;

    uint32_t getRPMForFan(int fan) override;
    bool getFanAutoControlMode(int fan) override;
    uint8_t getFanThrottle(int fan) override;

    void updateFanRPMS() override;
    void updateFanControl() override;

    void overrideFanControl(int fan, uint8_t thr) override;
    void setDefaultFanControl(int fan) override;

  private:
    static constexpr uint16_t kFAN_MAIN_CTRL_REG = 0x13;
    static constexpr uint16_t kFAN_RPM_REGS[] = {0x0d, 0x0e, 0x0f, 0x80, 0x82};
    static constexpr uint16_t kFAN_RPM_EXT_REGS[] = {0x18, 0x19, 0x1a, 0x81, 0x83};
    static constexpr uint16_t kFAN_PWM_CTRL_REGS[] = {0x15, 0x16, 0x17, 0x7f, 0xa7};
    static constexpr uint16_t kFAN_PWM_CTRL_EXT_REGS[] = {0x63, 0x6b, 0x73, 0x7b, 0xa3};

    int lpcPortSel = 0;

    uint16_t chipAddr = 0;
    uint8_t fanDefaultControlMode[IT86XXE_MAX_NUMFAN];
    uint8_t fanDefaultExtControlMode[IT86XXE_MAX_NUMFAN];

    uint8_t readByte(uint16_t addr);
    uint16_t readWord(uint16_t addr);

    void writeByte(uint16_t addr, uint8_t val);
};

#endif /* ISSuperIOIT86XXE_hpp */
