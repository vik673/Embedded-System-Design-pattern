#include "AbstractTransformChecker.h"
#include "Channel.h"

void AbstractTransformChecker::setCurrentChannel(Channel* channel) {
    itsChannel = channel;
}

void AbstractTransformChecker::setAlternativeChannel(Channel* channel) {
    itsOtherChannel = channel;
}

void AbstractTransformChecker::switchToAlternativeChannel() {
    if (itsChannel && itsOtherChannel) {
        itsChannel->disable();
        itsOtherChannel->enable();
    }
}

Channel* AbstractTransformChecker::getCurrentChannel() const {
    return itsChannel;
}

Channel* AbstractTransformChecker::getAlternativeChannel() const {
    return itsOtherChannel;
}
