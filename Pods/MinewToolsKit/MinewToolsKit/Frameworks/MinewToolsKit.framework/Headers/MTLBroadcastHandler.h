//
//  MTLBroadcastHandler.h
//  MinewSensorKit
//
//  Created by Minewtech on 2019/8/6.
//  Copyright © 2019 Minewtech. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MTLBroadcastHandler : NSObject

// name of device, sometimes available
@property (nonatomic, copy) NSString *name;

// current rssi value
@property (nonatomic, assign) NSInteger rssi;

// mac string, sometimes available
@property (nonatomic, copy) NSString *mac;

// identifier string, sometimes available
@property (nonatomic, copy) NSString *identifier;

// firm version string, sometimes available
@property (nonatomic, copy) NSString *firmVersion;

// hardware version string, sometimes available
@property (nonatomic, copy) NSString *hardwareVersion;

// battery value, sometimes available
@property (nonatomic, assign) int battery;

// smart lock state string, sometimes available
// smart lock state;0:lock;1:unlock;2:breakdown
@property (nonatomic, copy) NSString *smartLockState;

// chip info string, sometimes available
@property (nonatomic, copy) NSString *chipInfo;

// peripheral support string, sometimes available
@property (nonatomic, copy) NSString *peripheralSupport;


@end
