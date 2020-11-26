//
//  MTLPeripheral.h
//  MinewSensorKit
//
//  Created by Minewtech on 2019/8/5.
//  Copyright © 2019 Minewtech. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MTLConnectionHandler.h"
#import "MTLBroadcastHandler.h"


@interface MTLPeripheral : NSObject

// Uniquely identifier like "MAC address"
@property (nonatomic, strong) NSString *identifier;

// advertising stage handler
@property (nonatomic, strong) MTLBroadcastHandler *broadcast;

// connection stage handler
@property (nonatomic, strong) MTLConnectionHandler *connector;


@end

