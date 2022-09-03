#include "control_operator_interface.hpp"

#include <tap/communication/serial/remote.hpp>

namespace control
{
ControlOperatorInterafce::ControlOperatorInterafce(tap::communication::serial::Remote &remote)
    : remote(remote)
{
}

// Step 2: Add getChassisTankLeftInput and getChassisTankRightInput function definitions
}  // namespace control
