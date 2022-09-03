#pragma once

namespace tap::communication::serial
{
class Remote;
}

namespace control
{
class ControlOperatorInterafce
{
public:
    ControlOperatorInterafce(tap::communication::serial::Remote &remote);

    // Step 1: Add getChassisTankLeftInput and getChassisTankRightInput function declarations

private:
    tap::communication::serial::Remote &remote;
};
}  // namespace control
