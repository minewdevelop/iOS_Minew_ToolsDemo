//
//  DeviceVC.m
//  MinewToolsKitDemo
//
//  Created by minew on 2020/10/15.
//

#import "DeviceVC.h"
#import <MinewToolsKit/MTLOTAManager.h>

typedef NS_ENUM(NSUInteger, TargetType) {
    TargetTypeUnlock = 100,
    TargetTypeReadDeviceInfo,
    TargetTypeOTA,
};

@interface DeviceVC ()

@end

@implementation DeviceVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.title = _peripheral.connector.macString;
    self.view.backgroundColor = [UIColor whiteColor];
    
    
    [self initView];
    
}


// MARK: - Target Method
- (void)senderMethod:(UIButton *)sender {
    NSInteger tag = sender.tag;
    
    if (tag == 100) {
        // Unlock
        [_peripheral.connector writeData:UnLockWrited];
        
        [_peripheral.connector didUnlock:^(BOOL isSuccess, NSError * _Nonnull error) {
            if(isSuccess) {
                NSLog(@"Unlock Success");
                [self pop];
            } else {
                NSLog(@"Unlock Failed");
                [self pop];
            }
        }];
        
    } else if(tag == 101) {
        // Read Deveice Info
        [_peripheral.connector writeData:ReadDeviceInfoWrited];
        
        [_peripheral.connector didReadDeviceInfo:^(MTLDeviceInfo * _Nonnull deviceInfo, BOOL isSuccess, NSError * _Nonnull error) {
            if(isSuccess) {
                NSLog(@"ReadDeviceInfo Success: deviceType:%ld, firmVersion:%@, deviceState:%ld", deviceInfo.deviceType, deviceInfo.firmwareVersion, deviceInfo.deviceState);
                [self pop];
            } else {
                NSLog(@"ReadDeviceInfo Failed");
                [self pop];
            }
            
            
        }];
        
    } else {
        // OTA
        NSData *targetData = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"L1_OTA_ES009_20201119_v1_0_1" ofType:@".bin"]];
        [MTLOTAManager startOTAUpdate:_peripheral.connector OTAData:targetData progressHandler:^(float progress) {
            
            NSLog(@"ota progress: %f", progress);
            
        } completionHandler:^(BOOL isSuccess, NSError * _Nonnull error) {
            NSLog(@"ota success:%@", isSuccess ? @"Yes" : @"NO");
            [self pop];
        }];
    }

}

- (void)pop {
    [_manager disconnectFromPeriperal:_peripheral];
    [self.navigationController popViewControllerAnimated:YES];
}

/// MARK: - Views
- (void)initView {
    
    CGFloat screenWidth = [UIScreen mainScreen].bounds.size.width, eachHeight = 50, margin = 20;
;
    
    NSArray *titleArr = @[@"Unlock", @"Read DeviceInfo", @"OTA"];
    for (NSInteger i = 0; i < titleArr.count; i++) {
        UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(30, 150+(eachHeight+margin)*i, screenWidth-60, eachHeight)];
        [btn setBackgroundColor:[UIColor brownColor]];
        [btn setTitle:titleArr[i] forState:UIControlStateNormal];
        btn.titleLabel.textColor = [UIColor whiteColor];
        btn.tag = i+100;
        [btn addTarget:self action:@selector(senderMethod:) forControlEvents:UIControlEventTouchUpInside];
        [self.view addSubview:btn];
    }
}

@end
