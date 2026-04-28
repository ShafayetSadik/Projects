const FORM_ID = '10dwSmlWLh4hVQcW9E-z0PEOG9D_Rm1_WfjhavsxAHm4';
const SHEET_ID = '140EHSDhhMHDPp5t3YhM_SAg86blUNI1GY6hSoZt0asE';
const PEOPLE_CONFIG = [
  'Mohammad Ashfaqur Rahman Asif',
  'Md. huchnuch Sowab',
  'FAIAZ SAAD',
  'Faek Bin Rahman',
  'Fatema Tasnim Oyshi',
  'Tahsin Jawad',
  'Kushal Muhammed Haider',
  'Farhan Abrar',
  'Kaspia Ayshee',
  'Al Mahdi Akash',
  'Shah Laheen Mashahad',
  'Ferdaus Zamal',
  'Ashiqur Rahman',
  'Feehad kamal',
  'Elmul Soad Swopno',
  'K M ISTIAQUE',
  'Safwan Sami',
  'Most. Rezwana Tabassum',
  'Mayesha Aanan Prapti',
  'MD. FIROZ HOSSAIN',
  'Mutakabbir Ashfak',
  'MD Wahiduzzaman',
  'Natasha Hasan',
  'Zabin Tazrin Nashita',
  'Sayeed Hossain Sayor',
  'Muhtasim Zunaid Islam',
  'Rafid Mahmud',
  'M.M.Sadman Shafi',
  'Md. Rahib-Bin-Hossain',
  'Md. Muhidur Rahman',
  'Md. Mustak Hossain Simanto',
  'Shafin Ibnul Mohasin',
  'Tahmid Rahman',
  'K. M. Sirazul Monir',
  'Shafayet Sadik Sowad',
  'Shouvik Fahim',
  'Faiyaj Abrar',
  'Mohamed-Rachad Moussa',
  'Were Shuraim',
  'Iftikhar Azad Ifti',
  'Abubakar Sadiq Babangida',
  'Kouyate mouhamed',
  'Fatimatou Zaharaddine',
  'Mubarak Ibrahim',
  'Mohamed saed jama',
  'Zakariaou Ibrahim'
];

const TOTAL_PEOPLE = PEOPLE_CONFIG.length;

function onFormSubmit(e) {
  console.log('=== FORM SUBMIT TRIGGERED ===');
  console.log('Time: 2025-08-16 11:29:01 (UTC)');
  console.log('User: ShafayetSadik');
  
  try {
    // Log all submitted responses with proper mapping
    if (e && e.response) {
      const itemResponses = e.response.getItemResponses();
      console.log(`Total item responses: ${itemResponses.length}`);
      
      itemResponses.forEach((itemResponse, index) => {
        const newResponse = itemResponse.getResponse();
        const questionTitle = itemResponse.getItem().getTitle();
        const itemId = itemResponse.getItem().getId();
        console.log(`Response ${index + 1} - Item ID: ${itemId} - Title: "${questionTitle}" - Answer: "${newResponse}"`);
      });
    }
    
    // Brief wait for Google to save the response
    console.log('Processing responses...');
    Utilities.sleep(1000);
    
    // Update all form choices with proper mapping
    console.log('Updating all form choices with CORRECT mapping...');
    updateAllFormChoicesWithCorrectMapping();
    
    console.log('Form update complete - nicknames mapped to CORRECT person');
    console.log('Total processing time: ~2-3 seconds');
    
  } catch (error) {
    console.log('Error in form submit handler: ' + error.toString());
    console.log('Attempting fallback update...');
    
    // Fallback with longer wait
    Utilities.sleep(2000);
    updateAllFormChoicesWithCorrectMapping();
  }
}


function updateAllFormChoicesWithCorrectMapping() {
  console.log('=== UPDATING ALL FORM CHOICES WITH CORRECT MAPPING ===');
  console.log('Current Time: 2025-08-16 11:29:01 (UTC)');
  console.log('Updated by: ShafayetSadik');
  const startTime = new Date();
  
  try {
    // Access form and get all responses
    const form = FormApp.openById(FORM_ID);
    const responses = form.getResponses();
    console.log(`Processing ${responses.length} responses for ${TOTAL_PEOPLE} people`);
    
    // Get ALL items in the form to understand the structure
    const allItems = form.getItems();
    console.log(`Total form items: ${allItems.length}`);
    
    // Find ONLY the multiple choice items and their positions
    const mcqItems = [];
    const mcqItemIds = [];
    
    allItems.forEach((item, index) => {
      console.log(`Item ${index}: Type=${item.getType()}, Title="${item.getTitle()}", ID=${item.getId()}`);
      
      if (item.getType() === FormApp.ItemType.MULTIPLE_CHOICE) {
        mcqItems.push(item.asMultipleChoiceItem());
        mcqItemIds.push(item.getId());
        console.log(`  -> Multiple Choice Item #${mcqItems.length} found for: ${PEOPLE_CONFIG[mcqItems.length - 1]}`);
      }
    });
    
    console.log(`Found ${mcqItems.length} multiple choice questions for ${TOTAL_PEOPLE} people`);
    
    // Initialize SEPARATE nickname sets for each person
    const nicknamesByPerson = {};
    PEOPLE_CONFIG.forEach((person, index) => {
      nicknamesByPerson[index] = new Set();
    });
    
    // Process all responses with CORRECT mapping
    responses.forEach((response, responseIndex) => {
      console.log(`\n--- Processing Response ${responseIndex + 1} ---`);
      const itemResponses = response.getItemResponses();
      
      // Map each response to the CORRECT person by matching item IDs
      itemResponses.forEach((itemResponse, responseQuestionIndex) => {
        const answer = itemResponse.getResponse();
        const itemId = itemResponse.getItem().getId();
        
        // Find which person this response belongs to by matching item ID
        const correctPersonIndex = mcqItemIds.indexOf(itemId);
        
        if (correctPersonIndex !== -1 && correctPersonIndex < TOTAL_PEOPLE) {
          const personName = PEOPLE_CONFIG[correctPersonIndex];
          console.log(`  Response "${answer}" -> CORRECTLY mapped to ${personName} (Person ${correctPersonIndex + 1})`);
          
          if (answer && typeof answer === 'string') {
            const cleanNickname = answer.trim();
            if (cleanNickname.length > 0 && cleanNickname.length <= 50) {
              // Add nickname to the CORRECT person's set
              nicknamesByPerson[correctPersonIndex].add(cleanNickname);
            }
          }
        } else {
          console.log(`  Response "${answer}" -> SKIPPED (not a person question or invalid person index)`);
        }
      });
    });
    
    // Update each person's question with THEIR OWN nicknames only
    for (let personIndex = 0; personIndex < TOTAL_PEOPLE; personIndex++) {
      if (personIndex < mcqItems.length) {
        const mcqItem = mcqItems[personIndex];
        
        // Get nicknames ONLY for this specific person
        const uniqueNicknamesForThisPerson = Array.from(nicknamesByPerson[personIndex]).sort();
        
        console.log(`\n--- Updating ${PEOPLE_CONFIG[personIndex]} (Person ${personIndex + 1}) ---`);
        console.log(`  Unique nicknames: ${uniqueNicknamesForThisPerson.length}`);
        console.log(`  Nicknames: ${uniqueNicknamesForThisPerson.join(', ')}`);
        
        // Create new choice array with ONLY this person's nicknames
        const newChoices = uniqueNicknamesForThisPerson.length === 0 
          ? [mcqItem.createChoice(`No nicknames yet - be the first!`)]
          : uniqueNicknamesForThisPerson.map(nickname => mcqItem.createChoice(nickname));
        
        // Apply choices to form (SEPARATE for each person)
        mcqItem.setChoices(newChoices)
               .showOtherOption(true)
               .setRequired(false);
               
        console.log(`  Updated ${PEOPLE_CONFIG[personIndex]} with ${newChoices.length} choices`);
      }
    }
    
    const endTime = new Date();
    const processingTime = endTime - startTime;
    
    console.log('\n🎉 All form choices updated with CORRECT MAPPING');
    console.log(`Processing time: ${processingTime}ms`);
    console.log(' Fixed: Nicknames now go to the CORRECT person');
    console.log(' Third person nicknames will go to third person, not first person');
    console.log('Form ready for next submission');
    
  } catch (error) {
    console.log('Form update error: ' + error.toString());
    console.log('Attempting recovery...');
    
    // Recovery attempt
    try {
      const form = FormApp.openById(FORM_ID);
      const mcqItems = form.getItems(FormApp.ItemType.MULTIPLE_CHOICE);
      mcqItems.forEach((item, index) => {
        if (index < TOTAL_PEOPLE) {
          const mcqItem = item.asMultipleChoiceItem();
          mcqItem.showOtherOption(true).setRequired(false);
        }
      });
      console.log('Recovery successful - Other options ensured for all questions');
    } catch (recoveryError) {
      console.log('Recovery failed: ' + recoveryError.toString());
    }
  }
}

function debugFormStructure() {
  console.log('=== DEBUGGING FORM STRUCTURE ===');
  console.log('Debug time: 2025-08-16 11:29:01 (UTC)');
  console.log('Debugged by: ShafayetSadik');
  
  try {
    const form = FormApp.openById(FORM_ID);
    const allItems = form.getItems();
    const responses = form.getResponses();
    
    console.log(`\n FORM STRUCTURE:`);
    console.log(`Total items: ${allItems.length}`);
    console.log(`Total responses: ${responses.length}`);
    console.log(`Expected people: ${TOTAL_PEOPLE}`);
    
    // Show all items
    const mcqItems = [];
    allItems.forEach((item, index) => {
      const type = item.getType();
      const title = item.getTitle();
      const id = item.getId();
      
      console.log(`\nItem ${index + 1}: ${type}`);
      console.log(`  Title: "${title}"`);
      console.log(`  ID: ${id}`);
      
      if (type === FormApp.ItemType.MULTIPLE_CHOICE) {
        mcqItems.push({
          index: index,
          item: item.asMultipleChoiceItem(),
          id: id,
          title: title
        });
        console.log(`   This is MCQ #${mcqItems.length} for: ${PEOPLE_CONFIG[mcqItems.length - 1]}`);
      }
    });
    
    console.log(`\n MULTIPLE CHOICE MAPPING:`);
    mcqItems.forEach((mcqInfo, mcqIndex) => {
      console.log(`MCQ ${mcqIndex + 1}: "${mcqInfo.title}" (ID: ${mcqInfo.id}) -> ${PEOPLE_CONFIG[mcqIndex]}`);
    });
    
    // Check recent responses
    if (responses.length > 0) {
      console.log(`\n📝 RECENT RESPONSES (last 3):`);
      const recentResponses = responses.slice(-3);
      
      recentResponses.forEach((response, index) => {
        console.log(`\nResponse ${index + 1}:`);
        const itemResponses = response.getItemResponses();
        
        itemResponses.forEach((itemResponse, responseIndex) => {
          const answer = itemResponse.getResponse();
          const itemId = itemResponse.getItem().getId();
          const itemTitle = itemResponse.getItem().getTitle();
          
          // Find which person this should map to
          const correctPersonIndex = mcqItems.findIndex(mcqInfo => mcqInfo.id === itemId);
          const expectedPerson = correctPersonIndex !== -1 ? PEOPLE_CONFIG[correctPersonIndex] : 'UNKNOWN';
          
          console.log(`  Answer: "${answer}"`);
          console.log(`  Item ID: ${itemId}`);
          console.log(`  Item Title: "${itemTitle}"`);
          console.log(`  Should map to: ${expectedPerson}`);
          console.log(`  ---`);
        });
      });
    }
    
  } catch (error) {
    console.log('Error debugging form structure: ' + error.toString());
  }
}

function setupTriggers() {
  try {
    console.log('=== SETTING UP TRIGGERS ===');
    console.log('Setup time: 2025-08-16 11:29:01 (UTC)');
    console.log('Setup by: ShafayetSadik');
    
    // Remove existing triggers to prevent duplicates
    const existingTriggers = ScriptApp.getProjectTriggers();
    console.log(`Removing ${existingTriggers.length} existing triggers...`);
    
    existingTriggers.forEach((trigger, index) => {
      console.log(`Deleting trigger ${index + 1}: ${trigger.getHandlerFunction()}`);
      ScriptApp.deleteTrigger(trigger);
    });
    
    // Create form submit trigger
    const form = FormApp.openById(FORM_ID);
    const submitTrigger = ScriptApp.newTrigger('onFormSubmit')
                                   .forForm(form)
                                   .onFormSubmit()
                                   .create();
    
    console.log('Form submit trigger created');
    console.log('Trigger ID: ' + submitTrigger.getUniqueId());
    
    // Create backup time-based trigger (every 2 minutes for better performance)
    const backupTrigger = ScriptApp.newTrigger('updateAllFormChoicesWithCorrectMapping')
                                   .timeBased()
                                   .everyMinutes(2)
                                   .create();
    
    console.log('Backup trigger created (2-minute intervals)');
    console.log('Backup Trigger ID: ' + backupTrigger.getUniqueId());
    
    console.log('=== TRIGGERS READY ===');
    console.log('Expected update speed: 2-4 seconds');
    console.log(`System optimized for ${TOTAL_PEOPLE} people with CORRECT MAPPING`);
    
    return true;
    
  } catch (error) {
    console.log('Error setting up triggers: ' + error.toString());
    return false;
  }
}

function setupFormWithCorrectMapping() {
  try {
    console.log('=== STARTING CORRECT MAPPING FORM SETUP ===');
    console.log('Setup time: 2025-08-16 11:29:01 (UTC)');
    console.log('Setup by: ShafayetSadik');
    console.log(`Setting up CORRECT MAPPING for ${TOTAL_PEOPLE} people`);
    
    const form = FormApp.openById(FORM_ID);
    console.log('Form accessed successfully');
    
    // Set form metadata
    form.setTitle(`Section B Goru Party Names`)
        .setDescription(`Vote for nicknames for each person!`);
    
    console.log('Form title and description updated');
    
    // Remove all existing items for clean setup
    const items = form.getItems();
    console.log(`Removing ${items.length} existing items...`);
    
    for (let i = items.length - 1; i >= 0; i--) {
      form.deleteItem(items[i]);
    }
    console.log('Form cleared');
    
    // Add section header ONCE at the top
    const sectionHeader = form.addSectionHeaderItem();
    sectionHeader.setTitle('Choose from the options or give your preference in "other"')
                 
    
    // Create voting questions for each person (NO extra section headers between questions)
    console.log(`Creating ${TOTAL_PEOPLE} questions with CORRECT MAPPING...`);
    
    for (let i = 0; i < TOTAL_PEOPLE; i++) {
      const personName = PEOPLE_CONFIG[i];
      console.log(`Creating question ${i + 1} for ${personName}...`);
      
      // Create the voting question for this specific person
      const mcqItem = form.addMultipleChoiceItem();
      mcqItem.setTitle(`${i + 1}.${personName}`)
             
      
      // Create initial choice
      const initialChoice = mcqItem.createChoice(`Be the first!`);
      mcqItem.setChoices([initialChoice])
             .showOtherOption(true)
             .setRequired(false);
      
      console.log(`Question created for ${personName} (Position: ${i + 1})`);
    }
    
    // Add final thank you section
    const submitSection = form.addSectionHeaderItem();
    
           
    // Optimize form settings
    form.setCollectEmail(false)
        .setLimitOneResponsePerUser(false)
        .setShowLinkToRespondAgain(true)
        .setConfirmationMessage('Thank you for your vote!');
    
    console.log('Form optimized with CORRECT MAPPING');
    
    // Display setup results
    console.log('=== CORRECT MAPPING FORM SETUP COMPLETE ===');
    console.log('Form URL: ' + form.getPublishedUrl());
    console.log('Form ID: ' + FORM_ID);
    console.log(`Questions created: ${TOTAL_PEOPLE}`);
    console.log('People configured:', PEOPLE_CONFIG);
    console.log('FIXED: Correct mapping implemented');
    console.log('Ready for correct voting');
    
    return form.getPublishedUrl();
    
  } catch (error) {
    console.log('Error in correct mapping form setup: ' + error.toString());
    throw error;
  }
}

function completeSetupWithCorrectMapping() {
  console.log('=== COMPLETE FIXED SYSTEM SETUP ===');
  console.log('Setup started: 2025-08-16 11:29:01 (UTC)');
  console.log('Setup by: ShafayetSadik');
  console.log(`Target: FIXED voting system for ${TOTAL_PEOPLE} people`);
  
  try {
    // Step 1: Setup form with correct mapping
    console.log('\nSTEP 1: Setting up form with CORRECT MAPPING...');
    const formUrl = setupFormWithCorrectMapping();
    console.log('CORRECT MAPPING form setup complete');
    
    // Step 2: Setup triggers  
    console.log('\nSTEP 2: Setting up triggers...');
    const triggersSuccess = setupTriggers();
    console.log('Triggers setup complete');
    
    // Step 3: Debug form structure
    console.log('\nSTEP 3: Debugging form structure...');
    debugFormStructure();
    
    // Step 4: Initial update test
    console.log('\nSTEP 4: Testing CORRECT MAPPING update system...');
    updateAllFormChoicesWithCorrectMapping();
    console.log('CORRECT MAPPING update test complete');
    
    console.log('\n=== FIXED SYSTEM SETUP COMPLETE ===');
    console.log('Your FIXED voting system is ready!');
    console.log(`People configured: ${TOTAL_PEOPLE}`);
    console.log('People list:', PEOPLE_CONFIG);
    console.log('FIXED: Third person nicknames go to third person');
    console.log('FIXED: Each person has separate nickname lists');
    console.log('Form URL: ' + formUrl);
    console.log('System optimized by: ShafayetSadik');
    console.log('Setup date: 2025-08-16');
    
    return {
      success: true,
      formUrl: formUrl,
      peopleCount: TOTAL_PEOPLE,
      peopleList: PEOPLE_CONFIG,
      fixApplied: 'Correct person mapping implemented',
      setupBy: 'ShafayetSadik',
      setupDate: '2025-08-16'
    };
    
  } catch (error) {
    console.log('Setup error: ' + error.toString());
    return {
      success: false,
      error: error.toString()
    };
  }
}


function testTheFixManually() {
  console.log('=== TESTING THE FIX MANUALLY ===');
  console.log('Test time: 2025-08-16 11:29:01 (UTC)');
  console.log('Tested by: ShafayetSadik');
  
  // Debug structure first
  debugFormStructure();
  
  // Then update with correct mapping
  updateAllFormChoicesWithCorrectMapping();
  
  console.log('=== MANUAL FIX TEST COMPLETE ===');
  console.log('If you add a nickname for the 3rd person, it should now go to the 3rd person');
}
