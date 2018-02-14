//
//  MenuViewController.m
//  Created by lukasz karluk on 12/12/11.
//

#import "MyAppViewController.h"

#import "OFAppViewController.h"
#import "ofApp.h"

@interface MyAppViewController()
@property (nonatomic, strong) ARSession *session;
@end

@implementation MyAppViewController


- (void)loadView {
    //ここが呼ばれてofApp(Session *session)が呼ばれるみたいな。なのでsetup, contructorより前！
    [super loadView];
    
//    //SFormatに設定を書き込んで、新しくsessionを始めるみたいな。公式ではinitのとこで設定周りが書かれてるからexampleもそうしたらしい。
//    ARCore::SFormat format;
//    format.enableLighting();
//    //自動でplane detectionするので、anchorsに自動的にaddされてしまう→out of indexエラー発生する
////    format.enablePlaneTracking().enableLighting();
//    self.session = ARCore::generateNewSession(format);
    
    
    OFAppViewController *viewController;
    viewController = [[[OFAppViewController alloc] initWithFrame:[[UIScreen mainScreen] bounds]
                                                                 app:new ofApp()] autorelease];
    
    [self.navigationController setNavigationBarHidden:TRUE];
    [self.navigationController pushViewController:viewController animated:NO];
    self.navigationController.navigationBar.topItem.title = @"ofApp";
}


- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    BOOL bRotate = NO;
    bRotate = bRotate || (toInterfaceOrientation == UIInterfaceOrientationPortrait);
    bRotate = bRotate || (toInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
    bRotate = bRotate || (toInterfaceOrientation == UIInterfaceOrientationLandscapeLeft);
    bRotate = bRotate || (toInterfaceOrientation == UIInterfaceOrientationLandscapeRight);
    return bRotate;
}

@end
