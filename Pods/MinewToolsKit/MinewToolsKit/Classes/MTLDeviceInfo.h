//
//  MTLDeviceInfo.h
//  shoppingCar
//
//  Created by Apple on 2020/5/6.
//  Copyright © 2020 minew. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MTLDeviceType) {
    DeviceTypeSmartLock = 1,
    DeviceTypeOtherDevice,
};

typedef NS_ENUM(NSUInteger, MTLDeviceState) {
    DeviceStateLock = 1,
    DeviceStateUnlock,
    DeviceStateEquipmentFailure,
};

@interface MTLDeviceInfo : NSObject


// Device Type , Distinguish whether it is a shopping cart lock or other types of equipment
@property (nonatomic, assign) MTLDeviceType deviceType;

// Firmware Version
@property (nonatomic, strong) NSString *firmwareVersion;

// Device State，The state of the shopping cart lock, distinguish the lock state, unlock state and equipment failure state.
@property (nonatomic, assign) MTLDeviceState deviceState;

@end

NS_ASSUME_NONNULL_END

